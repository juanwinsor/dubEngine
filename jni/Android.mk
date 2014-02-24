LOCAL_PATH := $(call my-dir)

#-- glm
include $(CLEAR_VARS)
LOCAL_MODULE := glm
#LOCAL_SRC_FILES := core/libs/glm
LOCAL_C_INCLUDES := $(LOCAL_PATH)/core/libs/glm
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/libs/glm/core
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/libs/glm/gtc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/libs/glm/gtx
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/libs/glm/virtrev
include $(BUILD_STATIC_LIBRARY)

#-- Core Static Lib
include $(CLEAR_VARS)
LOCAL_MODULE := engineCore
#LOCAL_SRC_FILES := core/core.cpp core/graphics/Renderer.cpp core/BaseTypes.h core/hardware/DeviceInfo.h core/graphics/Camera2D.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/core
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/graphics
LOCAL_C_INCLUDES += $(LOCAL_PATH)/core/hardware
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_STATIC_LIBRARIES += glm
MY_NATIVE_TYPES := core/BaseTypes.h
LOCAL_CPPFLAGS += -include $(MY_NATIVE_TYPES) 
include $(BUILD_STATIC_LIBRARY)

#-- Main Shared Lib
include $(CLEAR_VARS)

LOCAL_MODULE    := dubEngine
LOCAL_SRC_FILES := main.cpp  game/Game.cpp
LOCAL_LDLIBS := -landroid -lGLESv2 -lEGL
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_STATIC_LIBRARIES += engineCore
LOCAL_STATIC_LIBRARIES += glm

MY_NATIVE_TYPES := core/BaseTypes.h
LOCAL_CPPFLAGS += -include $(MY_NATIVE_TYPES) 

include $(BUILD_SHARED_LIBRARY)



#include $(CLEAR_VARS)
#
#LOCAL_MODULE    := dubEngine
#LOCAL_SRC_FILES := main.cpp core/core.cpp core/graphics/Renderer.cpp game/Game.cpp
#LOCAL_LDLIBS := -landroid -lGLESv2 -lEGL
#LOCAL_STATIC_LIBRARIES := android_native_app_glue
#
#include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)