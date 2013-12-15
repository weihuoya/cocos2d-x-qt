#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

# build shared or static libraries, or static_and_shared (this is not supported
# by Symbian toolchains)
#
CONFIG += static

# Uncomment the following define to enable a very ugly hack to set the
# volume level on Symbian devices higher. By default, on Symbian, the volume
# level is very low when audio is played using QAudioOutput class. For now,
# this ugly hack is the only way to set the volume louder.
#
# WARNING: The volume hack (see the PullAudioOut.cpp file) is VERY DANGEROUS
# because the data to access the volume interface is retrieved manually with
# pointer manipulation. Should the library, in which the interface is
# implemented, be modified even a tiny bit, the application using this hack
# might crash.
#
#DEFINES += QTGAMEENABLER_USE_VOLUME_HACK

# Uncomment to decode ogg vorbis files on-the-fly. If this is commented out,
# the ogg vorbis files are decoded into memory when loading them.
#
DEFINES += USE_VORBIS_SOURCE

#-----------------------------------------------------------------------------

# Do not touch these

MOC_DIR = .moc
OBJECTS_DIR = .obj
DESTDIR = .lib

CONFIG += no_keywords
QT += core
contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols
QMAKE_CFLAGS += -std=c99

DEFINES += \
    SYSTEM_QT \
    COCOS2DXQT_LIBRARY

release {
    QMAKE_CFLAGS += -fomit-frame-pointer -funswitch-loops -march=armv7-a -mfpu=vfpv3
    QMAKE_CXXFLAGS += -fomit-frame-pointer -funswitch-loops -march=armv7-a -mfpu=vfpv3
    QMAKE_LFLAGS += -march=armv7-a -Wl,--fix-cortex-a8
}

symbian {
    DEFINES += Q_OS_SYMBIAN
}

contains(MEEGO_EDITION,harmattan) {
    DEFINES += MEEGO_EDITION_HARMATTAN
    DEFINES += CC_ENABLE_BOX2D_INTEGRATION
}
