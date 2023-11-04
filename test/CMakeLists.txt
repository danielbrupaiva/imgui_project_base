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
add_subdirectory($ENV{DEPENDENCIES_FOLDER}/vendor/Catch2
    $ENV{DEPENDENCIES_FOLDER}/vendor/Catch2/$ENV{BUILD_FOLDER}
)
target_link_libraries(${PROJECT_NAME} Catch2 Catch2WithMain )

