/**
 * Copyright (c) 2012 Nokia Corporation.
 * All rights reserved.
 *
 * Part of the Qt GameEnabler.
 *
 * For the applicable distribution terms see the license text file included in
 * the distribution.
 */

#ifndef GEOggSource_H
#define GEOggSource_H

#include <QPointer>
#include "geglobal.h"
#include "audiosourceif.h"

namespace GE {

// Forward declarations
class VorbisDecoder;

class Q_GE_EXPORT VorbisSource : public PlayableAudioSource
{
    Q_OBJECT

public:
    VorbisSource(QObject *parent = 0);
    virtual ~VorbisSource();

public: // From AudioSource
    int pullAudio(AUDIO_SAMPLE_TYPE *target, int bufferLength);

public:
    void setSpeed(float speed);
    void seek(quint64 samplePos);
    quint64 length();
    int sampleRate();

    bool load(QString filename);

protected:
    int mixBlock(AUDIO_SAMPLE_TYPE *target, int bufferLength);

Q_SIGNALS:
    void finished();

protected: // Data
    VorbisDecoder *m_decoder;
};

} // namespace GE

#endif // GEOggSource_H
