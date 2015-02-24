LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Splash.cpp \
                   ../../Classes/MainMenu.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/AnimationMoves.cpp \
                   ../../Classes/CollisionManager.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/EnemyFactory.cpp \
                   ../../Classes/HUD.cpp \
                   ../../Classes/Parallax.cpp \
                   ../../Classes/GameOver.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/CollectableFactory.cpp \
                   ../../Classes/SpawnManager.cpp \
                   ../../Classes/WorldManager.cpp \
                   ../../Classes/DAO/GameDAO.cpp \
                   ../../Classes/DAO/User.cpp \
                   ../../cocos2d/external/tinyxml2/tinyxml2.cpp                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../cocos2d/external/tinyxml2

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
