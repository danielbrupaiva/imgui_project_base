cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME tests)
project(${PROJECT_NAME} LANGUAGES CXX)
message("${BoldGreen}${PROJECT_NAME} BUILD ${ColourReset}")
###############################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############################################################################################
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
   message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
###############################################################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES
    test_case_1.cpp
)
add_executable(${PROJECT_NAME}
    main.cpp
    ${SOURCES}
)
###############################################################################################
include(GNUInstallDirs)
install(TARGETS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
###############################################################################################
include(FetchContent)
FetchContent_Declare(Catch2                              # name of the content
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git  # the repository
  GIT_TAG        devel                                   # the tag
  )
FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
target_link_libraries(${PROJECT_NAME} Catch2 Catch2WithMain )

