#####################################################################
# Muneeb Ahmad                                                      #
# Build for all architectures                                       #
#####################################################################

APP_ABI := all

#enable rtti
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti -Wno-psabi