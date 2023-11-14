###############################################################################################
# define processor architecture (triple)
set(TARGET_ARCHITECTURE aarch64-linux-gnu )
set(ARCH_GCC aarch64-beagle-linux-gnu)
# define target sysroot
set(TARGET_SYSROOT /dependencies/sysroot/beagleplay)
# define toolchain location
set(TARGET_TOOLCHAIN /dependencies/toolchain/${ARCH_GCC})
# define compiler C/CXX
set(CMAKE_C_COMPILER ${TARGET_TOOLCHAIN}/bin/${ARCH_GCC}-gcc)
set(CMAKE_CXX_COMPILER ${TARGET_TOOLCHAIN}/bin/${ARCH_GCC}-g++)
# define C/CXX flags
set(CMAKE_C_FLAGS  )
set(CMAKE_CXX_FLAGS )
# force cmake c/cxx compiler works
set(CMAKE_C_COMPILER_WORKS ON)
set(CMAKE_CXX_COMPILER_WORKS ON)
# define PKG config
set(ENV{PKG_CONFIG_PATH} $PKG_CONFIG_PATH:${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig)
# define PKG LIBDIR config
set(ENV{PKG_CONFIG_LIBDIR} ${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig:${TARGET_SYSROOT}/usr/lib/pkgconfig)
set(CMAKE_SYSROOT ${TARGET_SYSROOT})
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
# where is the target enviroment located
set(CMAKE_FIND_ROOT_PATH $ENV{TARGET_TOOLCHAIN} )
# adjust the default behavior of FIND_XXX() command
# search programs in the host enviroment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# search headers and libraries in the target enviroment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
#
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH $ENV{TARGET_SYSROOT})

