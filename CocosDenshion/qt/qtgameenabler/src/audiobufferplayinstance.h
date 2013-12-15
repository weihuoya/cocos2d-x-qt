/**
 * Copyright (c) 2011-2012 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the Qt GameEnabler.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef GEAUDIOBUFFERPLAYINSTANCE_H
#define GEAUDIOBUFFERPLAYINSTANCE_H

#include <QPointer>
#include "geglobal.h"
#include "audiosourceif.h"

namespace GE {

// Forward declarations
class AudioBuffer;


class Q_GE_EXPORT AudioBufferPlayInstance : public PlayableAudioSource
{
    Q_OBJECT

public:
    AudioBufferPlayInstance(AudioBuffer *buffer = 0, QObject *parent = 0);
    virtual ~AudioBufferPlayInstance();

public:
    bool isPlaying() const;

public: // From PlayableAudioSource
    int pullAudio(AUDIO_SAMPLE_TYPE *target, int bufferLength);

public Q_SLOTS:
    void playBuffer(AudioBuffer *buffer, int loopCount = 0);
    void playBuffer(AudioBuffer *buffer,
                    float volume,
                    float speed,
                    int loopCount = 0);
    void stop();
    void setSpeed(float speed);
    void seek(quint64 samplePos);
    quint64 length();
    int sampleRate();

protected:
    int mixBlock(AUDIO_SAMPLE_TYPE *target, int bufferLength);

protected: // Data
    QPointer<AudioBuffer> m_buffer; // Not owned
};

} // namespace GE

#endif // GEAUDIOBUFFERPLAYINSTANCE_H
