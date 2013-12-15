/**
 * Copyright (c) 2011-2012 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the Qt GameEnabler.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include "audiobufferplayinstance.h"
#include "audiobuffer.h"
#include "trace.h"

using namespace GE;

// Constants
const float GEMaxAudioSpeedValue(4096.0f);
const float GEDefaultAudioVolume(1.0f); // 1.0 => 100 %
const float GEDefaultAudioSpeed(1.0f); // 1.0 => 100 %


/*!
 * \class AudioBufferPlayInstance
 * \brief An AudioSource instance capable of playing a single audio buffer.
 */


/*!
  Constructor. If \a buffer is not NULL, it is set as the buffer to play.
*/
AudioBufferPlayInstance::AudioBufferPlayInstance(AudioBuffer *buffer /* = 0 */,
                                                 QObject *parent /* = 0 */)
    : PlayableAudioSource(parent),
      m_buffer(0)
{
    DEBUG_POINT;
    if (buffer) {
        // Start playing the given buffer.
        playBuffer(buffer, GEDefaultAudioVolume, GEDefaultAudioSpeed);
    }
}


/*!
  Destructor.
*/
AudioBufferPlayInstance::~AudioBufferPlayInstance()
{
    DEBUG_POINT;
}


/*!
  Returns true if the buffer is set, false otherwise.
*/
bool AudioBufferPlayInstance::isPlaying() const
{
    if (!m_buffer.isNull())
        return true;

    return false;
}


/*!
  From AudioSource.

  Returns an audio stream from the current sample.
*/
int AudioBufferPlayInstance::pullAudio(AUDIO_SAMPLE_TYPE *target,
                                       int bufferLength)
{
    if (m_buffer.isNull() || m_paused) {
        return 0;
    }

    unsigned int divider(m_buffer->getNofChannels() * m_buffer->getBytesPerSample());
    unsigned int channelLength(0);

    // Check in case of division by zero.
    if (divider) {
        channelLength = m_buffer->getDataLength() / divider - 2;
    }
    else {
        DEBUG_INFO("Warning: Catched division by zero error!");
    }

    unsigned int samplesToWrite(bufferLength / 2);
    unsigned int amount(0);
    unsigned int totalMixed(0);

    while (samplesToWrite > 0) {
        unsigned int samplesLeft;

        if (m_fixedInc == 0) {
            // No speed set. Will lead to division by zero error if not set.
            setSpeed(GEDefaultAudioSpeed);
        }

        samplesLeft = m_fixedInc > 0 ? channelLength - (m_fixedPos >> 12) :
            (m_fixedPos >> 12);

        // This is how much we can mix at least.
        unsigned int maxMixAmount = (int)(((long long int)(samplesLeft) << 12) /
                                 qAbs(m_fixedInc));

        if (maxMixAmount > samplesToWrite) {
            maxMixAmount = samplesToWrite;
        }

        if (maxMixAmount > 0) {
            amount = mixBlock(target+totalMixed * 2, maxMixAmount);

            if (amount == 0) {
                // Error!
                break;
            }

            totalMixed += amount;
        }
        else {
            amount = 0;
            m_fixedPos = m_fixedInc > 0 ? channelLength<<12 : 0;
        }

        // The sample ended. Check the looping variables and see what to do.
        if ((m_fixedPos >> 12) >= channelLength || m_fixedPos <= 0) {
            m_fixedPos += m_fixedInc > 0 ? -((qint64)channelLength << 12) :
                ((qint64)channelLength << 12);
            if (m_loopCount > 0)
                m_loopCount--;

            if (m_loopCount == 0) {
                // No more loops, stop the sample and return the amount of
                // samples already mixed.
                stop();
                break;
            }
        }

        samplesToWrite -= amount;

        if (samplesToWrite < 1)
            break;
    }

    return totalMixed * 2;
}


/*!
  Sets \a buffer as the audio buffer and will repeat the buffer according to
  \a loopCount. Note: If the given loop count is -1, the buffer will be
  repeated forever.
*/
void AudioBufferPlayInstance::playBuffer(AudioBuffer *buffer,
                                         int loopCount /* = 0 */)
{
    m_buffer = buffer;
    m_loopCount = loopCount;
    m_fixedPos = 0;
    m_paused = false;
}


/*!
  For convenience.

  In addition to playBuffer(AudioBuffer*, int) method, will also set \a volume
  and \a speed.
*/
void AudioBufferPlayInstance::playBuffer(AudioBuffer *buffer,
                                         float volume,
                                         float speed,
                                         int loopCount /* = 0 */)
{
    setLeftVolume(volume);
    m_fixedRightVolume = m_fixedLeftVolume;
    setSpeed(speed);
    playBuffer(buffer, loopCount);
}

/*!
  Resets the local buffer i.e. gets rid of the set buffer.
*/
void AudioBufferPlayInstance::stop()
{
    m_buffer = 0;
    PlayableAudioSource::stop();
}

/*!
  Sets \a speed as the speed of which the buffer is played in. The given
  argument value should not be zero. 1.0 indicates 100 % forward speed, -1.0
  100 % reverse speed.
*/
void AudioBufferPlayInstance::setSpeed(float speed)
{
    if (m_buffer.isNull())
        return;
    
    m_speed = speed;
    m_fixedInc = (int)(((float)m_buffer->getSamplesPerSec() *
        GEMaxAudioSpeedValue * speed) / (float)AUDIO_FREQUENCY);
    
    if (!m_fixedInc)
    {
        m_speed = 1.0f;
        m_fixedInc = 1;
    }
}

/*
  Sets playback position to given value. The given argument is in units of PCM
  audio samples per channel. 0 indicates beginning of the buffer and -1 the
  end of the buffer.
*/
void AudioBufferPlayInstance::seek(quint64 samplePos)
{
    if (m_buffer.isNull())
        return;

    const unsigned int channelLength = m_buffer->getDataLength() /
        m_buffer->getNofChannels() / m_buffer->getBytesPerSample();

    if (samplePos > channelLength - 2)
        samplePos = channelLength - 2;
#ifdef QTGAMEENABLER_SUPPORT_LONG_SAMPLES
    m_fixedPos = (quint64)samplePos << 12;
#else
    m_fixedPos = samplePos << 12;
#endif
}

/*!
  Return the length of the stream in units of PCM audio samples per
  channel.
*/
quint64 AudioBufferPlayInstance::length()
{
    if (m_buffer.isNull())
        return 0;

    return m_buffer->getDataLength() / m_buffer->getNofChannels();
}

int AudioBufferPlayInstance::sampleRate()
{
    if (m_buffer.isNull())
        return 0;

    return m_buffer->getSamplesPerSec();
}

/*!
  TODO: Document this method.

  Note: Does not do any bound checking, must be checked before called!
*/
int AudioBufferPlayInstance::mixBlock(AUDIO_SAMPLE_TYPE *target,
                                      int samplesToMix)
{
    SAMPLE_FUNCTION_TYPE sampleFunction = m_buffer->getSampleFunction();

    if (!sampleFunction) {
        // Unsupported sample type.
        return 0;
    }

    AUDIO_SAMPLE_TYPE *t_target = target + samplesToMix * 2;
    unsigned int sourcepos(0);

    int fixedLeftVolume = m_fixedLeftVolume;
    int fixedRightVolume = m_fixedRightVolume;
    unsigned int fadeInLen = m_fadeInDuration * m_buffer->getSamplesPerSec();
    unsigned int fadeOutLen = m_fadeOutDuration * m_buffer->getSamplesPerSec();

    if (m_buffer->getNofChannels() == 2) {
        // Stereo
        while (target != t_target) {
            sourcepos = m_fixedPos >> 12;

            if (fadeOutLen > 0 && length() - sourcepos < fadeOutLen) {
                fixedLeftVolume = (length() - sourcepos) * m_fixedLeftVolume / fadeOutLen;
                fixedRightVolume = (length() - sourcepos) * m_fixedRightVolume / fadeOutLen;
            } else if (fadeInLen > 0 && sourcepos < fadeInLen) {
                fixedLeftVolume = sourcepos * m_fixedLeftVolume / fadeInLen;
                fixedRightVolume = sourcepos * m_fixedRightVolume / fadeInLen;
            }

            target[0] = (((((sampleFunction)
                            (m_buffer, sourcepos, 0) *
                            (4096 - (m_fixedPos & 4095)) +
                            (sampleFunction)(m_buffer, sourcepos + 1, 0) *
                            (m_fixedPos & 4095)) >> 12) *
                          fixedLeftVolume) >> 12);

            target[1] = (((((sampleFunction)
                            (m_buffer, sourcepos, 1) *
                            (4096 - (m_fixedPos & 4095)) +
                            (sampleFunction)(m_buffer, sourcepos + 1, 1) *
                            (m_fixedPos & 4095) ) >> 12) *
                          fixedRightVolume) >> 12);

            m_fixedPos += m_fixedInc;
            target += 2;
        }
    }
    else {
        // Mono
        int temp(0);

        while (target != t_target) {
            sourcepos = m_fixedPos >> 12;

            if (fadeOutLen > 0 && length() - sourcepos < fadeOutLen) {
                fixedLeftVolume = (length() - sourcepos) * m_fixedLeftVolume / fadeOutLen;
                fixedRightVolume = (length() - sourcepos) * m_fixedRightVolume / fadeOutLen;
            } else if (fadeInLen > 0 && sourcepos < fadeInLen) {
                fixedLeftVolume = sourcepos * m_fixedLeftVolume / fadeInLen;
                fixedRightVolume = sourcepos * m_fixedRightVolume / fadeInLen;
            }

            temp = (((sampleFunction)(m_buffer, sourcepos, 0 ) *
                     (4096 - (m_fixedPos & 4095)) +
                     (sampleFunction)(m_buffer, sourcepos + 1, 0) *
                     (m_fixedPos & 4095)) >> 12);

            target[0] = ((temp * fixedLeftVolume) >> 12);
            target[1] = ((temp * fixedRightVolume) >> 12);

            m_fixedPos += m_fixedInc;
            target += 2;
        }
    }

    return samplesToMix;
}
