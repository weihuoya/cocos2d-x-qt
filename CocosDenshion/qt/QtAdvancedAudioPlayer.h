/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#ifndef QTADVANCEDAUDIOPLAYER_H_
#define QTADVANCEDAUDIOPLAYER_H_

#include "AdvancedAudioEngine.h"
#include "audiomixer.h"
#include "audioout.h"
#include "audiobuffer.h"
#include "vorbissource.h"
#include "audiobufferplayinstance.h"

#include <QVariant>
#include <QList>

using namespace GE;

namespace CocosDenshion {

class EXPORT_DLL QtAdvancedAudioPlayer : public QObject,
        public AdvancedAudioEngine
{
    Q_OBJECT

public:
    QtAdvancedAudioPlayer();
    virtual ~QtAdvancedAudioPlayer();

    virtual SfxId loadEffect(const char* pszFilePath);
    virtual SfxId loadMusic(const char* pszFilePath);
    virtual void unload(SfxId soundId);

    virtual void pauseAll();
    virtual void resumeAll();
    virtual void stopAll();

    virtual float getVolume();
    virtual void setVolume(float volume);

    virtual SfxInstanceId play(SfxId soundId);
    virtual void stop(SfxInstanceId soundId);
    virtual void pause(SfxInstanceId soundId);
    virtual void resume(SfxInstanceId soundId);
    virtual bool isPlaying(SfxInstanceId soundId);
    virtual bool isPaused(SfxInstanceId soundId);

    virtual void setLoopCount(SfxInstanceId soundId, unsigned int loopCount);
    virtual unsigned int getLoopCount(SfxInstanceId soundId);

    virtual void setVolume(SfxInstanceId soundId, float volume);
    virtual float getVolume(SfxInstanceId soundId);

    virtual void setPitch(SfxInstanceId soundId, float pitch);
    virtual float getPitch(SfxInstanceId soundId);

    virtual void setPanning(SfxInstanceId soundId, float pan);
    virtual float getPanning(SfxInstanceId soundId);

    virtual void setFadeInDuration(SfxInstanceId soundId, float fadeInDuration);
    virtual void setFadeOutDuration(SfxInstanceId soundId, float fadeOutDuration);

    virtual void seek(SfxInstanceId soundId, float position);
    virtual float position(SfxInstanceId soundId);

    virtual void setAudioEventListener(AudioEventListener *listener);
    virtual void removeAudioEventListener();

    virtual SfxId sfxIdForFile(const char* pszFilePath);
    virtual SfxId sfxIdForInstance(SfxInstanceId soundId);
    virtual SfxInstanceId sfxInstanceIdForSfxId(SfxId soundId);
    virtual SfxInstanceId getActiveSfxInstanceId();
    virtual unsigned int getSfxInstanceCount();
    virtual SfxInstanceId getSfxInstance(unsigned int index);

public Q_SLOTS:
    void sfxFinished(unsigned int tag);

private:
    void init();
    void checkFinishedEffects();

private:
    AudioMixer *m_mixer;
    AudioOut *m_audioOut;
    QHash<unsigned int, QPointer<QObject> > m_effects;
    QHash<unsigned int, QPointer<PlayableAudioSource> > m_effectInstances;
    AudioEventListener *m_audioEventListener;
    unsigned int m_sfxInstanceId;
};

} /* namespace CocosDenshion */

#endif /* QTADVANCEDAUDIOPLAYER_H_ */
