cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)
###############################################################################################
set(PROJECT_NAME imgui_project_base)
project(${PROJECT_NAME} LANGUAGES CXX)
message("${BoldGreen}${PROJECT_NAME} BUILD ${ColourReset}")
###############################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############################################################################################
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/App )
###############################################################################################
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/logo.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/resources
    )
###############################################################################################
