#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

INCLUDEPATH += \
    $$PWD/.. \
    $$PWD/../lua \
    $$PWD/../tolua \
    $$PWD/../cocos2dx_support \
    $$PWD/../lua_extensions \
    $$PWD/../../../CocosDenshion/include \
    $$PWD/../../../cocos2dx/platform \ 
    $$PWD/../../../cocos2dx/platform/qt \
    $$PWD/../../../extensions \
    $$PWD/../../../external/chipmunk/include/chipmunk \
    $$PWD/../../../cocos2dx/platform/third_party/qt/zlib \
    $$PWD/../../../cocos2dx/platform/third_party/qt/libwebsockets

!contains(DEFINES, DONT_INCLUDE_LUA_SOURCES) {
contains(DEFINES,COCOS2DXQT_LIBRARY) {
SOURCES += \
    $$PWD/../lua/lgc.h \
    $$PWD/../lua/print.c \
    $$PWD/../lua/lcode.c \
    $$PWD/../lua/lparser.c \
    $$PWD/../lua/lstring.c \
    $$PWD/../lua/lstate.c \
    $$PWD/../lua/ltable.c \
    $$PWD/../lua/ldblib.c \
    $$PWD/../lua/lobject.h \
    $$PWD/../lua/lstrlib.c \
    $$PWD/../lua/ldebug.c \
    $$PWD/../lua/lapi.c \
    $$PWD/../lua/ldo.c \
    $$PWD/../lua/ltm.c \
    $$PWD/../lua/liolib.c \
    $$PWD/../lua/lua.c \
    $$PWD/../lua/lmathlib.c \
    $$PWD/../lua/lopcodes.c \
    $$PWD/../lua/lgc.c \
    $$PWD/../lua/lobject.c \
    $$PWD/../lua/lbaselib.c \
    $$PWD/../lua/lzio.c \
    $$PWD/../lua/lopcodes.h \
    $$PWD/../lua/lauxlib.c \
    $$PWD/../lua/ldump.c \
    $$PWD/../lua/linit.c \
    $$PWD/../lua/loadlib.c \
    $$PWD/../lua/luaconf.h \
    $$PWD/../lua/lcode.h \
    $$PWD/../lua/loslib.c \
    $$PWD/../lua/lfunc.h \
    $$PWD/../lua/lmem.c \
    $$PWD/../lua/ltablib.c \
    $$PWD/../lua/lundump.c \
    $$PWD/../lua/lvm.c \
    $$PWD/../lua/llex.c \
    $$PWD/../lua/lfunc.c \
    $$PWD/../tolua/tolua_to.c \
    $$PWD/../tolua/tolua_push.c \
    $$PWD/../tolua/tolua_map.c \
    $$PWD/../tolua/tolua_is.c \
    $$PWD/../tolua/tolua_event.c \
    $$PWD/../cocos2dx_support/CCBProxy.cpp \
    $$PWD/../cocos2dx_support/CCLuaBridge.cpp \
    $$PWD/../cocos2dx_support/CCLuaEngine.cpp \
    $$PWD/../cocos2dx_support/CCLuaStack.cpp \
    $$PWD/../cocos2dx_support/CCLuaValue.cpp \
    $$PWD/../cocos2dx_support/Cocos2dxLuaLoader.cpp \
    $$PWD/../cocos2dx_support/lua_cocos2dx_extensions_manual.cpp \
    $$PWD/../cocos2dx_support/Lua_extensions_CCB.cpp \
    $$PWD/../cocos2dx_support/Lua_web_socket.cpp \
    $$PWD/../cocos2dx_support/LuaCocos2d.cpp \
    $$PWD/../cocos2dx_support/tolua_fix.c \

# for quick
SOURCES += \
    $$PWD/../lua_extensions/lua_extensions.c \
    $$PWD/../lua_extensions/cjson/fpconv.c \
    $$PWD/../lua_extensions/cjson/lua_cjson.c \
    $$PWD/../lua_extensions/cjson/strbuf.c \
    $$PWD/../lua_extensions/lpack/lpack.c \
    $$PWD/../lua_extensions/lsqlite3/sqlite3.c \
    $$PWD/../lua_extensions/lsqlite3/lsqlite3.c \
    $$PWD/../lua_extensions/zlib/lua_zlib.c \
    $$PWD/../lua_extensions/filesystem/lfs.c \
    $$PWD/../lua_extensions/socket/auxiliar.c \
    $$PWD/../lua_extensions/socket/except.c \
    $$PWD/../lua_extensions/socket/inet.c \
    $$PWD/../lua_extensions/socket/luasocket.c \
    $$PWD/../lua_extensions/socket/luasocket_buffer.c \
    $$PWD/../lua_extensions/socket/luasocket_io.c \
    $$PWD/../lua_extensions/socket/mime.c \
    $$PWD/../lua_extensions/socket/options.c \
    $$PWD/../lua_extensions/socket/select.c \
    $$PWD/../lua_extensions/socket/socket_scripts.c \
    $$PWD/../lua_extensions/socket/tcp.c \
    $$PWD/../lua_extensions/socket/timeout.c \
    $$PWD/../lua_extensions/socket/udp.c \
#    $$PWD/../lua_extensions/socket/wsocket.c \


PUBLIC_HEADERS += \
    $$PWD/../lua/lzio.h \
    $$PWD/../lua/lgc.h \
    $$PWD/../lua/lobject.h \
    $$PWD/../lua/lua.h \
    $$PWD/../lua/lstate.h \
    $$PWD/../lua/ldo.h \
    $$PWD/../lua/lmem.h \
    $$PWD/../lua/lapi.h \
    $$PWD/../lua/lualib.h \
    $$PWD/../lua/lundump.h \
    $$PWD/../lua/llex.h \
    $$PWD/../lua/lmathlib.c \
    $$PWD/../lua/lparser.h \
    $$PWD/../lua/llimits.h \
    $$PWD/../lua/lstring.h \
    $$PWD/../lua/lopcodes.h \
    $$PWD/../lua/lauxlib.h \
    $$PWD/../lua/ltm.h \
    $$PWD/../lua/ldebug.h \
    $$PWD/../lua/luaconf.h \
    $$PWD/../lua/lcode.h \
    $$PWD/../lua/lfunc.h \
    $$PWD/../lua/ltable.h \
    $$PWD/../lua/lvm.h \
    $$PWD/../tolua/tolua++.h \
    $$PWD/../tolua/tolua_event.h \
    $$PWD/../cocos2dx_support/CCBProxy.h \
    $$PWD/../cocos2dx_support/CCLuaBridge.h \
    $$PWD/../cocos2dx_support/CCLuaEngine.h \
    $$PWD/../cocos2dx_support/CCLuaStack.h \
    $$PWD/../cocos2dx_support/CCLuaValue.h \
    $$PWD/../cocos2dx_support/Cocos2dxLuaLoader.h \
    $$PWD/../cocos2dx_support/LuaCocos2d.h \
    $$PWD/../cocos2dx_support/Lua_extensions_CCB.h \
    $$PWD/../cocos2dx_support/tolua_fix.h \

# for quick
PUBLIC_HEADERS += \
    $$PWD/../lua_extensions/lua_extensions.h \
    $$PWD/../lua_extensions/cjson/fpconv.h \
    $$PWD/../lua_extensions/cjson/lua_cjson.h \
    $$PWD/../lua_extensions/cjson/strbuf.h \
    $$PWD/../lua_extensions/lpack/lpack.h \
    $$PWD/../lua_extensions/lsqlite3/sqlite3.h \
    $$PWD/../lua_extensions/lsqlite3/lsqlite3.h \
    $$PWD/../lua_extensions/zlib/lua_zlib.h \
    $$PWD/../lua_extensions/filesystem/lfs.h \
    $$PWD/../lua_extensions/socket/auxiliar.h \
    $$PWD/../lua_extensions/socket/except.h \
    $$PWD/../lua_extensions/socket/inet.h \
    $$PWD/../lua_extensions/socket/luasocket.h \
    $$PWD/../lua_extensions/socket/luasocket_buffer.h \
    $$PWD/../lua_extensions/socket/luasocket_io.h \
    $$PWD/../lua_extensions/socket/mime.h \
    $$PWD/../lua_extensions/socket/options.h \
    $$PWD/../lua_extensions/socket/select.h \
    $$PWD/../lua_extensions/socket/socket.h \
    $$PWD/../lua_extensions/socket/socket_scripts.h \
    $$PWD/../lua_extensions/socket/tcp.h \
    $$PWD/../lua_extensions/socket/timeout.h \
    $$PWD/../lua_extensions/socket/udp.h \
#    $$PWD/../lua_extensions/socket/wsocket.h \


HEADERS += $${PUBLIC_HEADERS}
}
}
