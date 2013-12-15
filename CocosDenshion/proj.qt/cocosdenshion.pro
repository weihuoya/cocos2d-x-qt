#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

TARGET = cocosdenshion-qt
TEMPLATE = lib

QT += gui xml
CONFIG += mobility
MOBILITY += multimedia systeminfo sensors

include($$PWD/../../cocos2d-qt-common.pri)
include(cocosdenshion.pri)

symbian {
    TARGET.UID3 = 0xE8AB1201
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1

    # FIXME: Currently cocosdenshion uses fileutils from cocos2dx
    contains(CONFIG,shared) {
        LIBS += -lcocos2dx-qt
        LIBS += -llibEGL -llibGLESv2
        LIBS += -lcone -leikcore -lavkon
    }

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
        QMAKE_POST_LINK += if [ -e lib$${TARGET}.a ]; then cp lib$${TARGET}.a $$[QT_INSTALL_LIBS]; fi
    } else {
        staticlib.sources = lib$${TARGET}.a
        staticlib.path = $$[QT_INSTALL_LIBS]
        INSTALLS += staticlib
    }

    # FIXME: Currently cocosdenshion uses fileutils from cocos2dx
    contains(CONFIG,shared) {
        LIBS += -lcocos2dx-qt
        LIBS += -lpthread -lEGL -lGLESv2
    }

    target.path = /usr/lib
    INSTALLS += target
}
