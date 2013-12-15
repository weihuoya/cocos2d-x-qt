/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include "SimpleAudioEngine.h"
#include "QtAdvancedAudioPlayer.h"

namespace CocosDenshion {

static AdvancedAudioEngine* oAudioPlayer;
static SfxId musicId = 0;
static float effectVol = 1.0f;
static float musicVol = 1.0f;
static float masterVol = 0.7f;

SimpleAudioEngine::SimpleAudioEngine()
{
    oAudioPlayer = QtAdvancedAudioPlayer::sharedEngine();
    oAudioPlayer->setVolume(masterVol);
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
    oAudioPlayer->stopAll();
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
        bool bLoop)
{
    SfxId id = oAudioPlayer->loadMusic(pszFilePath);
    musicId = oAudioPlayer->play(id);
    oAudioPlayer->setLoopCount(musicId, bLoop ? -1 : 0);
    oAudioPlayer->setVolume(musicId, musicVol);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (bReleaseData)
        oAudioPlayer->unload(oAudioPlayer->sfxIdForInstance(musicId));
    else
        oAudioPlayer->stop(musicId);
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    oAudioPlayer->pause(musicId);
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    oAudioPlayer->resume(musicId);
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    oAudioPlayer->seek(musicId, 0.0f);
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return oAudioPlayer->isPlaying(musicId);
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    musicId = oAudioPlayer->loadMusic(pszFilePath);
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath,
        bool bLoop)
{
    SfxId id = oAudioPlayer->loadEffect(pszFilePath);
    SfxInstanceId soundId = oAudioPlayer->play(id);
    oAudioPlayer->setLoopCount(soundId, bLoop ? -1 : 0);
    oAudioPlayer->setVolume(soundId, effectVol);
    return (unsigned int)soundId;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    oAudioPlayer->stop((SfxInstanceId)nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    oAudioPlayer->loadEffect(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    oAudioPlayer->unload(oAudioPlayer->sfxIdForFile(pszFilePath));
}

void SimpleAudioEngine::pauseEffect(unsigned int uSoundId)
{
    oAudioPlayer->pause((SfxInstanceId)uSoundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    unsigned int cnt = oAudioPlayer->getSfxInstanceCount();
    for (unsigned int i = 0; i < cnt; i++) {
        SfxInstanceId id = oAudioPlayer->getSfxInstance(i);
        if (id != musicId) {
            oAudioPlayer->pause(id);
        }
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int uSoundId)
{
    oAudioPlayer->resume((SfxInstanceId)uSoundId);
}

void SimpleAudioEngine::resumeAllEffects()
{
    unsigned int cnt = oAudioPlayer->getSfxInstanceCount();
    for (unsigned int i = 0; i < cnt; i++) {
        SfxInstanceId id = oAudioPlayer->getSfxInstance(i);
        if (id != musicId) {
            oAudioPlayer->resume(id);
        }
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    unsigned int cnt = oAudioPlayer->getSfxInstanceCount();
    for (unsigned int i = 0; i < cnt; i++) {
        SfxInstanceId id = oAudioPlayer->getSfxInstance(i);
        if (id != musicId) {
            oAudioPlayer->stop(id);
        }
    }
}



//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return musicVol;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    if (volume < 0.0f)
        volume = 0.0f;
    if (volume > 1.0f)
        volume = 1.0f;
    musicVol = volume;
    oAudioPlayer->setVolume(musicId, musicVol);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return effectVol;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    unsigned int cnt = oAudioPlayer->getSfxInstanceCount();

    if (volume < 0.0f)
        volume = 0.0f;
    if (volume > 1.0f)
        volume = 1.0f;
    effectVol = volume;

    for (unsigned int i = 0; i < cnt; i++) {
        SfxInstanceId id = oAudioPlayer->getSfxInstance(i);
        if (id != musicId) {
            oAudioPlayer->setVolume(id, effectVol);
        }
    }
}

} // end of namespace CocosDenshion
