cmake_minimum_required(VERSION 3.5)
include(FetchContent)
###############################################################################################
set(PROJECT_NAME App)
project(${PROJECT_NAME} LANGUAGES CXX)
message("${BoldGreen}${PROJECT_NAME} BUILD ${ColourReset}")
###############################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############################################################################################
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
   message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
###############################################################################################
include(GNUInstallDirs)
install(TARGETS
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
###############################################################################################
set(SOURCES
    main.cpp
    user.hpp
    globals.hpp
    FSM.hpp
    app.hpp app.cpp
    iscreen.hpp
    ui_home_screen.h ui_home_screen.cpp
)
###############################################################################################
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
###############################################################################################
FetchContent_Declare(
    Core
    SOURCE_DIR $ENV{CORE_FOLDER}
)
FetchContent_MakeAvailable(Core)
FetchContent_GetProperties(Core)

target_link_libraries(${PROJECT_NAME} PUBLIC Core)
###############################################################################################
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/danielbrupaiva/imgui.git
    GIT_TAG 5f89c1934c4b8a7894029b5d83a6be9cd3ef2f34
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
###############################################################################################
