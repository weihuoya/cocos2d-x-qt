TARGET = extension
TEMPLATE = lib


QT += gui
# CONFIG += mobility
# MOBILITY += multimedia systeminfo sensors

include(../../cocos2d-qt-common.pri)
include(extension.pri)


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
