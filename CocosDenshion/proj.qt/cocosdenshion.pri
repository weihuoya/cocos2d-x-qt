#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

INCLUDEPATH += \
    $$PWD/../include \
    $$PWD/../qt/ \
    $$PWD/../qt/qtgameenabler/src \
    $$PWD/../../cocos2dx/platform/qt \
    $$PWD/../../cocos2dx/platform \
    $$PWD/../../cocos2dx/include \
    $$PWD/../../cocos2dx/cocoa \
    $$PWD/../../cocos2dx

symbian {
    LIBS += -lremconcoreapi -lremconinterfacebase -lmmfdevsound
}

!contains(DEFINES, DONT_INCLUDE_DENSHION_SOURCES) {
contains(DEFINES,COCOS2DXQT_LIBRARY) {
    include($$PWD/../qt/qtgameenabler/qtgameenableraudio.pri)

    SOURCES += \
        $$PWD/../qt/SimpleAudioEngine.cpp \
        $$PWD/../qt/QtAdvancedAudioPlayer.cpp

    HEADERS += \
        $$PWD/../include/SimpleAudioEngine.h \
        $$PWD/../include/Export.h \
        $$PWD/../qt/AdvancedAudioEngine.h \
        $$PWD/../qt/QtAdvancedAudioPlayer.h
}
}
