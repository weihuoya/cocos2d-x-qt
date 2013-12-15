#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

QMAKE_CFLAGS += -std=c99
QT += core gui xml
CONFIG += mobility
MOBILITY += multimedia systeminfo sensors
QT += meegographicssystemhelper
DEFINES += SYSTEM_QT
DEFINES += MEEGO_EDITION_HARMATTAN
QMAKE_LIBDIR += $$PWD/lib

contains(COCOSBUILDMODE, inc) {
    DEFINES += COCOS2DXQT_LIBRARY

    contains(COCOSMODULES, cocosdenshion) {
        include(CocosDenshion/proj.qt/cocosdenshion.pri)
    }

    contains(COCOSMODULES, box2d) {
        include(external/Box2D/proj.qt/box2d.pri)
    }

    contains(COCOSMODULES, chipmunk) {
        include(external/chipmunk/proj.qt/chipmunk.pri)
    }

    contains(COCOSMODULES, extension) {
        include(extensions/proj.qt/extension.pri)
        LIBS += -lextension
    }

    contains(COCOSMODULES, lua) {
        include(scripting/lua/proj.qt/lua.pri)
    }

    include(cocos2dx/proj.qt/cocos2dx-qt.pri)
} else {
    contains(COCOSBUILDMODE, shared) {
        contains(COCOSMODULES, cocosdenshion) {
            include(CocosDenshion/proj.qt/cocosdenshion.pri)
            LIBS += -lcocosdenshion-qt
        }

        # FIXME: box2d and chipmunk libs do not export anything
        # usefull. The sources are included into the
        # project for now.
        contains(COCOSMODULES, box2d) {
            include(external/Box2D/proj.qt/box2d.pri)
        }

        contains(COCOSMODULES, chipmunk) {
            include(external/chipmunk/proj.qt/chipmunk.pri)
        }

        contains(COCOSMODULES, extension) {
            include(extensions/proj.qt/extension.pri)
            LIBS += -lextension
        }

        contains(COCOSMODULES, lua) {
            include(scripting/lua/proj.qt/lua.pri)
            LIBS += -llua
        }

        include(cocos2dx/proj.qt/cocos2dx-qt.pri)
        LIBS += -lcocos2dx-qt
    } else {
        contains(COCOSBUILDMODE, static) {
            contains(COCOSMODULES, cocosdenshion) {
                DEFINES += DONT_INCLUDE_DENSHION_SOURCES
                include(CocosDenshion/proj.qt/cocosdenshion.pri)
                LIBS += -l:libcocosdenshion-qt.a
            }

            contains(COCOSMODULES, box2d) {
                DEFINES += DONT_INCLUDE_BOX2D_SOURCES
                include(external/Box2D/proj.qt/box2d.pri)
                LIBS += -l:libbox2d.a
            }

            contains(COCOSMODULES, chipmunk) {
                DEFINES += DONT_INCLUDE_CHIPMUNK_SOURCES
                include(external/chipmunk/proj.qt/chipmunk.pri)
                LIBS += -l:libchipmunk.a
            }

            contains(COCOSMODULES, extension) {
                DEFINES += DONT_INCLUDE_EXTENSION_SOURCES
                include(extensions/proj.qt/extension.pri)
                LIBS += -l:libextension.a
            }
            
            contains(COCOSMODULES, lua) {
                DEFINES += DONT_INCLUDE_LUA_SOURCES
                include(scripting/lua/proj.qt/lua.pri)
                LIBS += -l:liblua-qt.a
            }

            LIBS += -l:libcocos2dx-qt.a
            include(cocos2dx/proj.qt/cocos2dx-qt.pri)
        } else {
            error("COCOSBUILDMODE not defined!");
        }
    }
}
