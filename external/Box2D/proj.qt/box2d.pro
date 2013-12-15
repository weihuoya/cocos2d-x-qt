#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

TARGET = box2d
TEMPLATE = lib

include(../../../cocos2d-qt-common.pri)
include(box2d.pri)

symbian {
    TARGET.UID3 = 0xE8AB1205
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
        QMAKE_POST_LINK += if [ -e lib$${TARGET}.a ]; then cp lib$${TARGET}.a $$[QT_INSTALL_LIBS]; fi
    } else {
        staticlib.sources = lib$${TARGET}.a
        staticlib.path = $$[QT_INSTALL_LIBS]
        INSTALLS += staticlib
    }

    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
