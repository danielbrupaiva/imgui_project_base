###############################################################################################
set(ENV{TARGET_TRIPLET} "")
# define compiler
set(CMAKE_C_COMPILER)
set(CMAKE_CXX_COMPILER)
# define C/CXX flags
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} )
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

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

