#
# Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
#
# For the applicable distribution terms see the license text file included in
# the distribution.
#

INCLUDEPATH += \
    $$PWD/../include \
    $$PWD/../platform/qt \
    $$PWD/../platform \
    $$PWD/../support \
    $$PWD/../cocoa \
    $$PWD/../kazmath/include \
    $$PWD/../actions \
    $$PWD/../base_nodes \
    $$PWD/../effects \
    $$PWD/../label_nodes \
    $$PWD/../sprite_nodes \
    $$PWD/../script_support \
    $$PWD/../shaders \
    $$PWD/../textures \
    $$PWD/../touch_dispatcher \
    $$PWD/../menu_nodes \
    $$PWD/../misc_nodes \
    $$PWD/../keypad_dispatcher \
    $$PWD/../layers_scenes_transitions_nodes \
    $$PWD/../particle_nodes \
    $$PWD/../tileMap_parallax_nodes \
    $$PWD/../text_input_node \
    $$PWD/../ \
    $$PWD/../../extensions \
    $$PWD/../../extensions/CCBReader \
    $$PWD/../../extensions/GUI/CCControlExtension \
    $$PWD/../../extensions/GUI/CCControlExtension \
    $$PWD/../../external/chipmunk/include/chipmunk \
    $$PWD/../../extensions/network \
    $$PWD/../../extensions/Components \
    $$PWD/../platform/third_party/qt/zlib \
    $$PWD/../platform/third_party/qt/libwebp \
    $$PWD/../platform/third_party/qt/libjpeg \
    $$PWD/../platform/third_party/qt/libpng \
    $$PWD/../platform/third_party/qt/libtiff \


unix:!symbian {
    LIBS += -lpthread -lEGL -lGLESv2
}

symbian {
    LIBS += -llibEGL -llibGLESv2
    LIBS += -lcone -leikcore -lavkon
}

contains(DEFINES,COCOS2DXQT_LIBRARY) {
    SOURCES += \
        #actions \
        $$PWD/../actions/CCAction.cpp \
        $$PWD/../actions/CCActionCamera.cpp \
        $$PWD/../actions/CCActionEase.cpp \
        $$PWD/../actions/CCActionGrid.cpp \
        $$PWD/../actions/CCActionGrid3D.cpp \
        $$PWD/../actions/CCActionInstant.cpp \
        $$PWD/../actions/CCActionInterval.cpp \
        $$PWD/../actions/CCActionManager.cpp \
        $$PWD/../actions/CCActionPageTurn3D.cpp \
        $$PWD/../actions/CCActionProgressTimer.cpp \
        $$PWD/../actions/CCActionTiledGrid.cpp \
        $$PWD/../actions/CCActionCatmullRom.cpp \
        $$PWD/../actions/CCActionTween.cpp \
        #base_nodes \
        $$PWD/../base_nodes/CCAtlasNode.cpp \
        $$PWD/../base_nodes/CCNode.cpp \
        $$PWD/../base_nodes/CCGLBufferedNode.cpp \
        #cocoa \
        $$PWD/../cocoa/CCAffineTransform.cpp \
        $$PWD/../cocoa/CCAutoreleasePool.cpp \
        $$PWD/../cocoa/CCGeometry.cpp \
        $$PWD/../cocoa/CCNS.cpp \
        $$PWD/../cocoa/CCObject.cpp \
        $$PWD/../cocoa/CCSet.cpp \
        $$PWD/../cocoa/CCZone.cpp \
        $$PWD/../cocoa/CCArray.cpp \
        $$PWD/../cocoa/CCDictionary.cpp \
        $$PWD/../cocoa/CCString.cpp \
        $$PWD/../cocoa/CCDataVisitor.cpp \
        #draw_nodes \
        $$PWD/../draw_nodes/CCDrawingPrimitives.cpp \
        $$PWD/../draw_nodes/CCDrawNode.cpp \
        #effects \
        $$PWD/../effects/CCGrabber.cpp \
        $$PWD/../effects/CCGrid.cpp \
        #kazmath \
        $$PWD/../kazmath/src/aabb.c \
        $$PWD/../kazmath/src/plane.c \
        $$PWD/../kazmath/src/vec2.c \
        $$PWD/../kazmath/src/mat3.c \
        $$PWD/../kazmath/src/quaternion.c \
        $$PWD/../kazmath/src/vec3.c \
        $$PWD/../kazmath/src/mat4.c \
        $$PWD/../kazmath/src/ray2.c \
        $$PWD/../kazmath/src/vec4.c \
        $$PWD/../kazmath/src/neon_matrix_impl.c \
        $$PWD/../kazmath/src/utility.c \
        $$PWD/../kazmath/src/GL/mat4stack.c \
        $$PWD/../kazmath/src/GL/matrix.c \
        #keypad_dispatcher \
        $$PWD/../keypad_dispatcher/CCKeypadDelegate.cpp \
        $$PWD/../keypad_dispatcher/CCKeypadDispatcher.cpp \
        #label_nodes \
        $$PWD/../label_nodes/CCLabelAtlas.cpp \
        $$PWD/../label_nodes/CCLabelBMFont.cpp \
        $$PWD/../label_nodes/CCLabelTTF.cpp \
        #layers_scenes_transitions_nodes \
        $$PWD/../layers_scenes_transitions_nodes/CCLayer.cpp \
        $$PWD/../layers_scenes_transitions_nodes/CCScene.cpp \
        $$PWD/../layers_scenes_transitions_nodes/CCTransition.cpp \
        $$PWD/../layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
        $$PWD/../layers_scenes_transitions_nodes/CCTransitionProgress.cpp \
        #menu_nodes \
        $$PWD/../menu_nodes/CCMenu.cpp \
        $$PWD/../menu_nodes/CCMenuItem.cpp \
        #misc_nodes \
        $$PWD/../misc_nodes/CCMotionStreak.cpp \
        $$PWD/../misc_nodes/CCProgressTimer.cpp \
        $$PWD/../misc_nodes/CCClippingNode.cpp \
        $$PWD/../misc_nodes/CCRenderTexture.cpp \
        #particle_nodes \
        $$PWD/../particle_nodes/CCParticleExamples.cpp \
        $$PWD/../particle_nodes/CCParticleSystem.cpp \
        $$PWD/../particle_nodes/CCParticleSystemQuad.cpp \
        $$PWD/../particle_nodes/CCParticleBatchNode.cpp \
        #platform \
        $$PWD/../platform/CCSAXParser.cpp \
        $$PWD/../platform/CCThread.cpp \
        $$PWD/../platform/platform.cpp \
        $$PWD/../platform/CCImageCommonWebp.cpp \
        $$PWD/../platform/CCEGLViewProtocol.cpp \
        $$PWD/../platform/CCFileUtils.cpp \
        #script_support \
        $$PWD/../script_support/CCScriptSupport.cpp \
        #shaders \
        $$PWD/../shaders/CCGLProgram.cpp \
        $$PWD/../shaders/ccGLStateCache.cpp \
        $$PWD/../shaders/CCShaderCache.cpp \
        $$PWD/../shaders/ccShaders.cpp \
        #sprite_nodes \
        $$PWD/../sprite_nodes/CCAnimation.cpp \
        $$PWD/../sprite_nodes/CCAnimationCache.cpp \
        $$PWD/../sprite_nodes/CCSprite.cpp \
        $$PWD/../sprite_nodes/CCSpriteBatchNode.cpp \
        $$PWD/../sprite_nodes/CCSpriteFrame.cpp \
        $$PWD/../sprite_nodes/CCSpriteFrameCache.cpp \
        #support \
        $$PWD/../support/ccUTF8.cpp \
        $$PWD/../support/CCPointExtension.cpp \
        $$PWD/../support/CCProfiling.cpp \
        $$PWD/../support/TransformUtils.cpp \
        $$PWD/../support/base64.cpp \
        $$PWD/../support/ccUtils.cpp \
        $$PWD/../support/CCVertex.cpp \
        $$PWD/../support/CCNotificationCenter.cpp \
        $$PWD/../support/component/CCComponent.cpp \
        $$PWD/../support/component/CCComponentContainer.cpp \
        $$PWD/../support/data_support/ccCArray.cpp \
        $$PWD/../support/image_support/TGAlib.cpp \
        $$PWD/../support/tinyxml2/tinyxml2.cpp \
        $$PWD/../support/user_default/CCUserDefault.cpp \
        $$PWD/../support/zip_support/ZipUtils.cpp \
        $$PWD/../support/zip_support/ioapi.cpp \
        $$PWD/../support/zip_support/unzip.cpp \
        #text_input_node \
        $$PWD/../text_input_node/CCIMEDispatcher.cpp \
        $$PWD/../text_input_node/CCTextFieldTTF.cpp \
        #textures \
        $$PWD/../textures/CCTexture2D.cpp \
        $$PWD/../textures/CCTextureAtlas.cpp \
        $$PWD/../textures/CCTextureCache.cpp \
        $$PWD/../textures/CCTextureETC.cpp \
        $$PWD/../textures/CCTexturePVR.cpp \
        #tilemap_parallax_nodes \
        $$PWD/../tilemap_parallax_nodes/CCParallaxNode.cpp \
        $$PWD/../tilemap_parallax_nodes/CCTMXLayer.cpp \
        $$PWD/../tilemap_parallax_nodes/CCTMXObjectGroup.cpp \
        $$PWD/../tilemap_parallax_nodes/CCTMXTiledMap.cpp \
        $$PWD/../tilemap_parallax_nodes/CCTMXXMLParser.cpp \
        $$PWD/../tilemap_parallax_nodes/CCTileMapAtlas.cpp \
        #touch_dispatcher \
        $$PWD/../touch_dispatcher/CCTouchDispatcher.cpp \
        $$PWD/../touch_dispatcher/CCTouchHandler.cpp \
        $$PWD/../touch_dispatcher/CCTouch.cpp \
        # \
        $$PWD/../CCCamera.cpp \
        $$PWD/../CCConfiguration.cpp \
        $$PWD/../CCDirector.cpp \
        $$PWD/../CCScheduler.cpp \
        $$PWD/../ccFPSImages.c \
        $$PWD/../cocos2d.cpp 

## for quick        
#    SOURCES += \
#        $$PWD/../actions/CCLinkPosition.cpp \
#        $$PWD/../draw_nodes/CCShapeNode.cpp \
#        $$PWD/../misc_nodes/CCClippingRegionNode.cpp \
#        $$PWD/../platform/CCZipFile.cpp \
#        $$PWD/../sprite_nodes/CCGraySprite.cpp \
##        $$PWD/../cocoa/CCPointArray.cpp

#for qt
    SOURCES += \
        $$PWD/../platform/qt/CCImage.cpp \
        $$PWD/../platform/qt/CCFileUtilsLinux.cpp \
        $$PWD/../platform/qt/CCDevice.cpp \
        $$PWD/../platform/qt/CCEGLView.cpp \
        $$PWD/../platform/qt/CCApplication.cpp \
        $$PWD/../platform/qt/CCAccelerometer.cpp \
        $$PWD/../platform/qt/accelerometerfilter.cpp \
        $$PWD/../platform/qt/CCSAXParser.cpp \
        $$PWD/../platform/qt/CCCommon.cpp

    PUBLIC_HEADERS = \
        $$PWD/../text_input_node/CCIMEDelegate.h \
        $$PWD/../text_input_node/CCIMEDispatcher.h \
        $$PWD/../text_input_node/CCTextFieldTTF.h \
        $$PWD/../support/zip_support/ZipUtils.h \
        $$PWD/../support/zip_support/unzip.h \
        $$PWD/../support/zip_support/ioapi.h \
        $$PWD/../support/data_support/ccCArray.h \
        $$PWD/../support/data_support/utlist.h \
        $$PWD/../support/data_support/uthash.h \
        $$PWD/../support/image_support/TGAlib.h \
        $$PWD/../support/CCNotificationCenter.h \
        $$PWD/../support/CCPointExtension.h \
        $$PWD/../support/CCProfiling.h \
        $$PWD/../support/ccUTF8.h \
        $$PWD/../support/TransformUtils.h \
        $$PWD/../support/CCVertex.h \
        $$PWD/../support/ccUtils.h \
        $$PWD/../support/CCProfiling.h \
        $$PWD/../support/base64.h \
        $$PWD/../tileMap_parallax_nodes/CCParallaxNode.h \
        $$PWD/../tileMap_parallax_nodes/CCTMXObjectGroup.h \
        $$PWD/../tileMap_parallax_nodes/CCTileMapAtlas.h \
        $$PWD/../tileMap_parallax_nodes/CCTMXLayer.h \
        $$PWD/../tileMap_parallax_nodes/CCTMXXMLParser.h \
        $$PWD/../tileMap_parallax_nodes/CCTMXTiledMap.h \
        $$PWD/../platform/CCThread.h \
        $$PWD/../platform/platform.h \
        $$PWD/../platform/CCFileUtils.h \
        $$PWD/../platform/CCSAXParser.h \
        $$PWD/../platform/CCApplicationProtocol.h \
        $$PWD/../platform/CCPlatformConfig.h \
        $$PWD/../platform/CCEGLViewProtocol.h \
        $$PWD/../platform/CCDevice.h \
        $$PWD/../platform/CCCommon.h \
        $$PWD/../platform/CCImage.h \
        $$PWD/../platform/CCImageCommon_cpp.h \
        $$PWD/../platform/CCAccelerometerDelegate.h \
        $$PWD/../platform/CCPlatformMacros.h \
        $$PWD/../actions/CCAction.h \
        $$PWD/../actions/CCActionInterval.h \
        $$PWD/../actions/CCActionGrid3D.h \
        $$PWD/../actions/CCActionEase.h \
        $$PWD/../actions/CCActionPageTurn3D.h \
        $$PWD/../actions/CCActionProgressTimer.h \
        $$PWD/../actions/CCActionGrid.h \
        $$PWD/../actions/CCActionCamera.h \
        $$PWD/../actions/CCActionInstant.h \
        $$PWD/../actions/CCActionTiledGrid.h \
        $$PWD/../actions/CCActionTween.h \
        $$PWD/../actions/CCActionManager.h \
        $$PWD/../actions/CCActionCatmullRom.h \
        $$PWD/../label_nodes/CCLabelBMFont.h \
        $$PWD/../label_nodes/CCLabelAtlas.h \
        $$PWD/../label_nodes/CCLabelTTF.h \
        $$PWD/../layers_scenes_transitions_nodes/CCLayer.h \
        $$PWD/../layers_scenes_transitions_nodes/CCScene.h \
        $$PWD/../layers_scenes_transitions_nodes/CCTransition.h \
        $$PWD/../layers_scenes_transitions_nodes/CCTransitionProgress.h \
        $$PWD/../layers_scenes_transitions_nodes/CCTransitionPageTurn.h \
        $$PWD/../base_nodes/CCAtlasNode.h \
        $$PWD/../base_nodes/CCNode.h \
        $$PWD/../base_nodes/CCGLBufferedNode.h \
        $$PWD/../script_support/CCScriptSupport.h \
        $$PWD/../kazmath/include/kazmath/plane.h \
        $$PWD/../kazmath/include/kazmath/mat3.h \
        $$PWD/../kazmath/include/kazmath/vec3.h \
        $$PWD/../kazmath/include/kazmath/mat4.h \
        $$PWD/../kazmath/include/kazmath/aabb.h \
        $$PWD/../kazmath/include/kazmath/vec4.h \
        $$PWD/../kazmath/include/kazmath/kazmath.h \
        $$PWD/../kazmath/include/kazmath/neon_matrix_impl.h \
        $$PWD/../kazmath/include/kazmath/GL/mat4stack.h \
        $$PWD/../kazmath/include/kazmath/GL/matrix.h \
        $$PWD/../kazmath/include/kazmath/utility.h \
        $$PWD/../kazmath/include/kazmath/ray2.h \
        $$PWD/../kazmath/include/kazmath/quaternion.h \
        $$PWD/../kazmath/include/kazmath/vec2.h \
        $$PWD/../CCConfiguration.h \
        $$PWD/../menu_nodes/CCMenuItem.h \
        $$PWD/../menu_nodes/CCMenu.h \
        $$PWD/../include/cocos2d.h \
        $$PWD/../include/ccConfig.h \
        $$PWD/../include/ccTypes.h \
        $$PWD/../include/CCProtocols.h \
        $$PWD/../include/CCEventType.h \
        $$PWD/../include/ccMacros.h \
        $$PWD/../include/ccTypeInfo.h \
        $$PWD/../particle_nodes/CCParticleBatchNode.h \
        $$PWD/../particle_nodes/CCParticleSystemQuad.h \
        $$PWD/../particle_nodes/CCParticleExamples.h \
        $$PWD/../particle_nodes/CCParticleSystem.h \
        $$PWD/../particle_nodes/firePngData.h \
        $$PWD/../keypad_dispatcher/CCKeypadDelegate.h \
        $$PWD/../keypad_dispatcher/CCKeypadDispatcher.h \
        $$PWD/../shaders/ccShader_PositionTextureA8Color_frag.h \
        $$PWD/../shaders/CCShaderCache.h \
        $$PWD/../shaders/ccShader_PositionTextureColor_vert.h \
        $$PWD/../shaders/ccShader_PositionColor_vert.h \
        $$PWD/../shaders/CCGLProgram.h \
        $$PWD/../shaders/ccShader_PositionColor_frag.h \
        $$PWD/../shaders/ccShader_PositionTexture_frag.h \
        $$PWD/../shaders/ccShader_PositionTextureA8Color_vert.h \
        $$PWD/../shaders/ccShaderEx_SwitchMask_frag.h \
        $$PWD/../shaders/ccShader_PositionTexture_uColor_frag.h \
        $$PWD/../shaders/ccShader_PositionTexture_uColor_vert.h \
        $$PWD/../shaders/ccShader_PositionTextureColorAlphaTest_frag.h \
        $$PWD/../shaders/ccShader_PositionTexture_vert.h \
        $$PWD/../shaders/ccShader_PositionTextureColor_frag.h \
        $$PWD/../shaders/ccShader_Position_uColor_frag.h \
        $$PWD/../shaders/ccShaders.h \
        $$PWD/../shaders/ccShader_Position_uColor_vert.h \
        $$PWD/../shaders/ccGLStateCache.h \
        $$PWD/../shaders/ccShader_PositionColorLengthTexture_frag.h \
        $$PWD/../shaders/ccShader_PositionColorLengthTexture_vert.h \
        $$PWD/../CCDirector.h \
        $$PWD/../CCCamera.h \
        $$PWD/../CCScheduler.h \
        $$PWD/../misc_nodes/CCMotionStreak.h \
        $$PWD/../misc_nodes/CCProgressTimer.h \
        $$PWD/../misc_nodes/CCRenderTexture.h \
        $$PWD/../misc_nodes/CCClippingNode.h \
        $$PWD/../cocoa/CCAffineTransform.h \
        $$PWD/../cocoa/CCInteger.h \
        $$PWD/../cocoa/CCObject.h \
        $$PWD/../cocoa/CCAutoreleasePool.h \
        $$PWD/../cocoa/CCDictionary.h \
        $$PWD/../cocoa/CCSet.h \
        $$PWD/../cocoa/CCArray.h \
        $$PWD/../cocoa/CCNS.h \
        $$PWD/../cocoa/CCString.h \
        $$PWD/../cocoa/CCGeometry.h \
        $$PWD/../cocoa/CCBool.h \
        $$PWD/../cocoa/CCDataVisitor.h \
        $$PWD/../cocoa/CCDouble.h \
        $$PWD/../cocoa/CCFloat.h \
        $$PWD/../textures/CCTextureCache.h \
        $$PWD/../textures/CCTexture2D.h \
        $$PWD/../textures/CCTextureAtlas.h \
        $$PWD/../textures/CCTexturePVR.h \
        $$PWD/../textures/CCTextureETC.h \
        $$PWD/../sprite_nodes/CCAnimation.h \
        $$PWD/../sprite_nodes/CCAnimationCache.h \
        $$PWD/../sprite_nodes/CCSpriteFrame.h \
        $$PWD/../sprite_nodes/CCSpriteFrameCache.h \
        $$PWD/../sprite_nodes/CCSpriteBatchNode.h \
        $$PWD/../sprite_nodes/CCSprite.h \
        $$PWD/../touch_dispatcher/CCTouchHandler.h \
        $$PWD/../touch_dispatcher/CCTouchDelegateProtocol.h \
        $$PWD/../touch_dispatcher/CCTouchDispatcher.h \
        $$PWD/../touch_dispatcher/CCTouch.h \
        $$PWD/../ccFPSImages.h \
        $$PWD/../effects/CCGrid.h \
        $$PWD/../effects/CCGrabber.h

    HEADERS += $${PUBLIC_HEADERS}

    HEADERS += \
        $$PWD/../platform/qt/CCPlatformDefine.h \
        $$PWD/../platform/qt/CCApplication.h \
        $$PWD/../platform/qt/CCGL.h \
        $$PWD/../platform/qt/CCStdC.h \
        $$PWD/../platform/qt/CCEGLView.h \
        $$PWD/../platform/qt/CCFileUtilsLinux.h \
        $$PWD/../platform/qt/accelerometerfilter.h \
        $$PWD/../platform/qt/CCAccelerometer.h \
#        $$PWD/../platform/qt/CCApplicationPrivate.h \

    HEADERS += \
        $$PWD/../effects/CCGrid.h \
        $$PWD/../effects/CCGrabber.h \
        $$PWD/../cocoa/CCNS.h \
        $$PWD/../support/TransformUtils.h \
        $$PWD/../support/ccUtils.h \
        $$PWD/../support/base64.h \
        $$PWD/../support/CCPointExtension.h \
        $$PWD/../support/CCProfiling.h \
        $$PWD/../support/CCVertex.h \
        $$PWD/../support/data_support/ccCArray.h \
        $$PWD/../support/data_support/uthash.h \
        $$PWD/../support/data_support/utlist.h \
        $$PWD/../support/image_support/TGAlib.h \
        $$PWD/../support/zip_support/ZipUtils.h \
        $$PWD/../support/zip_support/unzip.h \
        $$PWD/../support/zip_support/ioapi.h
       
## for quick       
#    HEADERS += \
#        $$PWD/../actions/CCLinkPosition.h \
#        $$PWD/../draw_nodes/CCShapeNode.h \
#        $$PWD/../misc_nodes/CCClippingRegionNode.h \
#        $$PWD/../platform/CCZipFile.h \
#        $$PWD/../sprite_nodes/CCGraySprite.h \
#        $$PWD/../shaders/ccShader_PositionTextureGray_frag.h \
#        $$PWD/../cocoa/CCPointArray.h 
}
