###############################################################################################
set(ENV{DEPENDENCIES_FOLDER} ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

set(ENV{TARGET_TRIPLET} "x86_64-unknown-linux-gnu")
#set(ENV{TARGET_TRIPLET} "aarch64-beagle-linux-gnu")
#set(ENV{TARGET_TRIPLET} "aarch64-none-linux-gnu")

set(ENV{BUILD_FOLDER} "build_$ENV{TARGET_TRIPLET}")
set(ENV{TARGET_TOOLCHAIN} "")
set(ENV{TARGET_SYSROOT} "")

###############################################################################################
option(CROSS_COMPILER "CROSS COMPILER" OFF)
#if(CROSS_COMPILER)
#    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
#endif()

option(TARGET_SYSROOT "TARGET_SYSROOT" OFF)
if(TARGET_SYSROOT)
    set(ENV{TARGET_SYSROOT} $ENV{DEPENDENCIES_FOLDER}/sysroot)
endif()
###############################################################################################
message("${BoldYellow}-- CROSS COMPILER ${CROSS_COMPILER}${ColourReset}")
message("${BoldYellow}-- TARGET SYSROOT ${TARGET_SYSROOT}${ColourReset}")
message("${BoldYellow}-- Dependencies folder: $ENV{DEPENDENCIES_FOLDER}${ColourReset}")
message("${BoldYellow}-- Target sysroot folder: $ENV{TARGET_SYSROOT}${ColourReset}")
###############################################################################################
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()
###############################################################################################
