cmake_minimum_required(VERSION 3.5)
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
    global.hpp
    app.hpp app.cpp
)
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
###############################################################################################
add_subdirectory(/home/daniel/projects/imgui_project_base/dependencies/vendor/imgui
    /home/daniel/projects/imgui_project_base/dependencies/vendor/imgui/build$ENV{BUILD_FOLDER}
)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
###############################################################################################
