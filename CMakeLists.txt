cmake_minimum_required(VERSION 3.5)
include(FetchContent)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)
###############################################################################################
set(PROJECT_NAME imgui_project_base)
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

include(GNUInstallDirs)
install(TARGETS
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
###############################################################################################
set(SOURCES
    main.cpp
    app.h app.cpp
    filelogger.h
    database.h
)
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
###############################################################################################
#FetchContent_Declare(
#    imgui
#    GIT_REPOSITORY https://github.com/danielbrupaiva/imgui.git
#    GIT_TAG master
#    GIT_SHALLOW TRUE
#    GIT_PROGRESS TRUE
#)
#FetchContent_MakeAvailable(imgui)
#FetchContent_GetProperties(imgui)

add_subdirectory($ENV{DEPENDENCIES_FOLDER}/vendor/imgui
    $ENV{DEPENDENCIES_FOLDER}/vendor/imgui/build$ENV{BUILD_FOLDER}
)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
###############################################################################################
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/_logo.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources
    )
###############################################################################################
option(SKIP_BUILD_TEST ON)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_DOC OFF)
option(INSTALL_TEST OFF)
add_subdirectory($ENV{DEPENDENCIES_FOLDER}/vendor/libpqxx
    $ENV{DEPENDENCIES_FOLDER}/vendor/libpqxx/build$ENV{BUILD_FOLDER}
)
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)
###############################################################################################
