option(CROSS_COMPILER "Enable cross compiler?" ON)
message("${BoldYellow}-- Cross compiler: ${CROSS_COMPILER}${ColourReset}")
###############################################################################################
###############################################################################################
set(ARCH_GCC aarch64-beagle-linux-gnu)
# define processor architecture (triple)
set(TARGET_ARCHITECTURE aarch64-linux-gnu )
# define target sysroot
set(TARGET_SYSROOT /home/daniel/projects/imgui_project_base/dependencies/sysroot/beagleplay)
# define toolchain location
set(TARGET_TOOLCHAIN /home/daniel/projects/imgui_project_base/dependencies/toolchain/${ARCH_GCC})
# define compiler C/CXX
set(CMAKE_C_COMPILER ${TARGET_TOOLCHAIN}/bin/${ARCH_GCC}-gcc)
set(CMAKE_CXX_COMPILER ${TARGET_TOOLCHAIN}/bin/${ARCH_GCC}-g++)
# define C/CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${TARGET_SYSROOT}/usr/include -I${TARGET_SYSROOT}/usr/include/${TARGET_ARCHITECTURE}")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
# force cmake c/cxx compiler works
set(CMAKE_C_COMPILER_WORKS ON)
set(CMAKE_CXX_COMPILER_WORKS ON)
###############################################################################################
# define PKG config
set(ENV{PKG_CONFIG_PATH} $PKG_CONFIG_PATH:${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig)
## define PKG LIBDIR config
set(ENV{PKG_CONFIG_LIBDIR} ${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig:${TARGET_SYSROOT}/usr/lib/pkgconfig)
set(CMAKE_SYSROOT ${TARGET_SYSROOT})
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
## where is the target enviroment located
set(CMAKE_FIND_ROOT_PATH ${TARGET_SYSROOT} )
## adjust the default behavior of FIND_XXX() command
## search programs in the host enviroment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
## search headers and libraries in the target enviroment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
##
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${TARGET_SYSROOT})

set(XCB_PATH_VARIABLE ${TARGET_SYSROOT})

set(GL_INC_DIR ${TARGET_SYSROOT}/usr/include)
set(GL_LIB_DIR ${TARGET_SYSROOT}:${TARGET_SYSROOT}/usr/lib/aarch64-linux-gnu:${TARGET_SYSROOT}/usr:${TARGET_SYSROOT}/usr/lib)

set(EGL_INCLUDE_DIR ${GL_INC_DIR})
set(EGL_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libEGL.so)

set(OPENGL_INCLUDE_DIR ${GL_INC_DIR})
set(OPENGL_opengl_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libOpenGL.so)
set(OPENGL_glx_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libGLX.so)

set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
set(GLESv2_LIBRARY ${XCB_PATH_VARIABLE}/usr/lib/aarch64-linux-gnu/libGLESv2.so)

set(SDL_INCLUDE_DIRS ${TARGET_SYSROOT}/usr/local/include)
set(SDL_LIBRARIES ${TARGET_SYSROOT}/usr/local/lib)

set(SDL_IMAGE_INCLUDE_DIRS ${TARGET_SYSROOT}/usr/local/include)
set(SDL_IMAGE_LIBRARIES ${TARGET_SYSROOT}/usr/local/lib)
