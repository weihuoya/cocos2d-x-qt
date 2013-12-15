#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = CocosDenshion/proj.qt/cocosdenshion.pro
SUBDIRS += external/Box2D/proj.qt/box2d.pro
SUBDIRS += external/chipmunk/proj.qt/chipmunk.pro
SUBDIRS += cocos2dx/proj.qt/cocos2dx-qt.pro
SUBDIRS += scripting/lua/proj.qt/lua.pro
SUBDIRS += extensions/proj.qt/extension.pro

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
