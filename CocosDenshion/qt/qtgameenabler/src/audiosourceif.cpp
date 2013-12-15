/**
 * Copyright (c) 2011-2012 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the Qt GameEnabler.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#include "audiosourceif.h"

using namespace GE;


/*!
  \class AudioSource
  \brief An abstract interface for an audio source.
*/


/*!
  Constructor.
*/
AudioSource::AudioSource(QObject *parent /* = 0 */)
    : QObject(parent)
{
}


/*!
  Destructor.
*/
AudioSource::~AudioSource()
{
}


/*!
  This method is used to check whether this instance can be (auto-)destroyed
  or not.

  To be implemented in the derived class. This default implementation always
  returns false.
*/
bool AudioSource::canBeDestroyed()
{
    return false;
}

PlayableAudioSource::PlayableAudioSource(QObject *parent /* = 0 */)
  : AudioSource(parent),
    m_finished(false),
    m_destroyWhenFinished(true),
    m_paused(true),
    m_fixedPos(0),
    m_fixedInc(0),
    m_fixedLeftVolume((int)GEMaxAudioVolumeValue),
    m_fixedRightVolume((int)GEMaxAudioVolumeValue),
    m_loopCount(0),
    m_speed(0.0f),
    m_fadeInDuration(0.0f),
    m_fadeOutDuration(0.0f),
    m_tag(0),
    m_id(0)
{
}


/*!
  Destructor.
*/
PlayableAudioSource::~PlayableAudioSource()
{
}

/*!
  From AudioSource.

  The framework will use this to know whether this AudioSource can be
  destroyed or not.
*/
bool PlayableAudioSource::canBeDestroyed()
{
    if (m_finished && m_destroyWhenFinished)
        return true;

    return false;
}


/*!
  Sets \a volume for the left channel. The given argument value should be
  between 0.0 and 1.0 since 1.0 indicates 100 %.
*/
void PlayableAudioSource::setLeftVolume(float volume)
{
    m_fixedLeftVolume = (int)(GEMaxAudioVolumeValue * volume);
}


/*!
  Sets \a volume for the right channel. The given argument value should be
  between 0.0 and 1.0 since 1.0 indicates 100 %.
*/
void PlayableAudioSource::setRightVolume(float volume)
{
    m_fixedRightVolume = (int)(GEMaxAudioVolumeValue * volume);
}

/*!
  Play/resume playback.
*/
void PlayableAudioSource::play()
{
    m_finished = false;
    m_paused = false;
}

/*!
  Stop/pause playback. Calling play() after stop() continues playback from the
  position where the playback was stopped.
*/
void PlayableAudioSource::stop()
{
    m_finished = true;
    m_paused = false;
    Q_EMIT finished(getTag());
}


/*!
  Return the current playback position in units of PCM audio samples per
  channel.
*/
quint64 PlayableAudioSource::position()
{
    return (m_fixedPos >> 12);
}

void PlayableAudioSource::checkOverlappingFadeDurations()
{
    // TODO: ...
}

void PlayableAudioSource::setFadeInDuration(float duration)
{
    m_fadeInDuration = duration;
    checkOverlappingFadeDurations();
}

void PlayableAudioSource::setFadeOutDuration(float duration)
{
    m_fadeOutDuration = duration;
    checkOverlappingFadeDurations();
}
