#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

TARGET = cocos2dx-qt
TEMPLATE = lib

QT += xml gui meegographicssystemhelper
CONFIG += mobility
MOBILITY += systeminfo sensors

CONFIG(debug, debug|release) {
    # 0, or undefined: No debug messages
    # 1: No CCLOGINFO
    # >1: All
    DEFINES += COCOS2D_DEBUG=1
}

include(../../cocos2d-qt-common.pri)
include(cocos2dx-qt.pri)

symbian {
    TARGET.UID3 = 0xE8AB1200
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1

    MMP_RULES += EXPORTUNFROZEN
    MMP_RULES += "OPTION gcce -march=armv6"
    MMP_RULES += "OPTION gcce -mfpu=vfp"
    MMP_RULES += "OPTION gcce -mfloat-abi=softfp"
    MMP_RULES += "OPTION gcce -marm"
    MMP_RULES += "OPTION gcce -fno-use-cxa-atexit"

    addFiles.sources = $${TARGET}.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    contains(MEEGO_EDITION,harmattan) {
        QT += meegographicssystemhelper
        QMAKE_POST_LINK += if [ -e lib$${TARGET}.a ]; then cp lib$${TARGET}.a $$[QT_INSTALL_LIBS]; fi
    } else {
        staticlib.sources = lib$${TARGET}.a
        staticlib.path = $$[QT_INSTALL_LIBS]
        INSTALLS += staticlib
    }

    target.path = /usr/lib
    INSTALLS += target
}
