cmake_minimum_required(VERSION 3.5)
###############################################################################################
set(PROJECT_NAME Core)
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
    filelogger.hpp
    database.hpp
)
add_executable(${PROJECT_NAME}
    ${SOURCES}
)
###############################################################################################
option(SKIP_BUILD_TEST ON)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_DOC OFF)
option(INSTALL_TEST OFF)
add_subdirectory(/home/daniel/projects/imgui_project_base/dependencies/vendor/libpqxx
    /home/daniel/projects/imgui_project_base/dependencies/vendor/libpqxx/build$ENV{BUILD_FOLDER}
)
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)
###############################################################################################
