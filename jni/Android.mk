LOCAL_PATH := $(call my-dir)
WIENGINE_PATH := /Users/muneebahmad/Documents/WiEngine-master

###############################################################################
# <-- created by Muneeb Ahmad allowing undefined symbols warning -->          #
###############################################################################
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

LOCAL_DISABLE_FORMAT_STRING_CHECKS := true

################################################################################

###########################################################
## Find all of files under the named directories.         #
###########################################################

define all-cpp-files-under
$(patsubst ./%,%, \
	$(shell cd $(LOCAL_PATH) ; \
		find $(1) -name "*.cpp" -and -not -name ".*") \
)
endef

###############################################################################
#                                     <-- build muneebahmad lib -->           #
###############################################################################

include $(CLEAR_VARS)
LOCAL_MODULE := muneebahmad
LOCAL_CPPFLAGS += -Wno-psabi
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../external/$(TARGET_ARCH_ABI) -llog -ldl -lGLESv1_CM -lwiengine -llua -lchipmunk -lwisound -lbox2d -lwinetwork -liap

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Source \
	$(WIENGINE_PATH)/jni/ \
	$(WIENGINE_PATH)/jni/chipmunk \
	$(WIENGINE_PATH)/jni/chipmunk/constraints \
	$(WIENGINE_PATH)/jni/lua \
	$(WIENGINE_PATH)/jni/lua/tolua++ \
	$(WIENGINE_PATH)/jni/WiEngine/include \
	$(WIENGINE_PATH)/jni/WiEngine/include/actions \
	$(WIENGINE_PATH)/jni/WiEngine/include/afcanim \
	$(WIENGINE_PATH)/jni/WiEngine/include/astar \
	$(WIENGINE_PATH)/jni/WiEngine/include/bitmapfont \
	$(WIENGINE_PATH)/jni/WiEngine/include/box2d \
	$(WIENGINE_PATH)/jni/WiEngine/include/chipmunk \
	$(WIENGINE_PATH)/jni/WiEngine/include/common \
	$(WIENGINE_PATH)/jni/WiEngine/include/dialog \
	$(WIENGINE_PATH)/jni/WiEngine/include/easeactions \
	$(WIENGINE_PATH)/jni/WiEngine/include/events \
	$(WIENGINE_PATH)/jni/WiEngine/include/filters \
	$(WIENGINE_PATH)/jni/WiEngine/include/grid \
	$(WIENGINE_PATH)/jni/WiEngine/include/gridactions \
	$(WIENGINE_PATH)/jni/WiEngine/include/json \
	$(WIENGINE_PATH)/jni/WiEngine/include/lua \
	$(WIENGINE_PATH)/jni/WiEngine/include/iap \
	$(WIENGINE_PATH)/jni/WiEngine/include/nodes \
	$(WIENGINE_PATH)/jni/WiEngine/include/opengl \
	$(WIENGINE_PATH)/jni/WiEngine/include/particle \
	$(WIENGINE_PATH)/jni/WiEngine/include/persistence \
	$(WIENGINE_PATH)/jni/WiEngine/include/skeletalanim \
	$(WIENGINE_PATH)/jni/WiEngine/include/tmx \
	$(WIENGINE_PATH)/jni/WiEngine/include/transitions \
	$(WIENGINE_PATH)/jni/WiEngine/include/types \
	$(WIENGINE_PATH)/jni/WiEngine/include/winetwork \
	$(WIENGINE_PATH)/jni/WiEngine/include/wisound \
	$(WIENGINE_PATH)/jni/WiEngine/include/utils \
	$(WIENGINE_PATH)/jni/libxml2/include \
	$(WIENGINE_PATH)/jni/libpvr
	
	LOCAL_SRC_FILES := $(call all-cpp-files-under,Source)
	
	include $(BUILD_SHARED_LIBRARY)