/**
 * Copyright (c) 2011-2012 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the Qt GameEnabler.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef GEINTERFACES_H
#define GEINTERFACES_H

#include <QObject>


namespace GE {

#define AUDIO_FREQUENCY 22050
#define AUDIO_SAMPLE_TYPE short
#define AUDIO_SAMPLE_BITS 16
#define AUDIO_CHANNELS 2

// Constants
const float GEMaxAudioVolumeValue(4096.0f);


class AudioSource : public QObject
{
    Q_OBJECT

public:
    explicit AudioSource(QObject *parent = 0);
    virtual ~AudioSource();

public:
    virtual bool canBeDestroyed();
    virtual int pullAudio(AUDIO_SAMPLE_TYPE *target, int bufferLength ) = 0;
};

class PlayableAudioSource : public AudioSource
{
    Q_OBJECT

public:
    explicit PlayableAudioSource(QObject *parent = 0);
    virtual ~PlayableAudioSource();

public:
    virtual bool canBeDestroyed();
    virtual int pullAudio(AUDIO_SAMPLE_TYPE *target, int bufferLength ) = 0;

public:
    inline bool isFinished() const { return m_finished; }
    inline bool isPaused() const { return m_paused; }
    inline void setDestroyWhenFinished(bool set) { m_destroyWhenFinished = set; }
    inline bool destroyWhenFinished() const { return m_destroyWhenFinished; }
    inline void setTag(unsigned int tag) { m_tag = tag; }
    inline unsigned int getTag() { return m_tag; }
    inline void setId(unsigned int id) { m_id = id; }
    inline unsigned int getId() { return m_id; }

    virtual void setLoopCount(int count) { m_loopCount = count; }
    virtual int getLoopCount() { return m_loopCount; }

    virtual float leftVolume() { return m_fixedLeftVolume / 4096.0f; }
    virtual float rightVolume() { return m_fixedRightVolume / 4096.0f; }

    virtual void pause() { m_paused = true; }
    virtual void resume() { m_paused = false; }

    virtual void setSpeed(float speed) = 0;
    virtual float getSpeed() { return m_speed; }

    virtual void setLeftVolume(float volume);
    virtual void setRightVolume(float volume);

    virtual void seek(quint64 samplePos) = 0;
    virtual quint64 position();
    virtual quint64 length() = 0;

    virtual int sampleRate() = 0;

    virtual void setFadeInDuration(float duration);
    virtual void setFadeOutDuration(float duration);

    virtual void play();
    virtual void stop();

Q_SIGNALS:
    void finished(unsigned int);

private:
    void checkOverlappingFadeDurations();

protected:
    bool m_finished;
    bool m_destroyWhenFinished;
    bool m_paused;
    quint64 m_fixedPos;
    int m_fixedInc;
    int m_fixedLeftVolume;
    int m_fixedRightVolume;
    int m_loopCount;
    float m_speed;
    float m_fadeInDuration;
    float m_fadeOutDuration;
    unsigned int m_tag;
    unsigned int m_id;
};


} // namespace GE

#endif // GEINTERFACES_H
