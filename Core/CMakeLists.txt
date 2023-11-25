cmake_minimum_required(VERSION 3.5)
include(FetchContent)
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
    include/filelogger.hpp
    include/database.hpp
)
###############################################################################################
add_library(${PROJECT_NAME} STATIC )
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} )
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
###############################################################################################
if(${CROSS_COMPILER})
    find_package(pqxx REQUIRED)
else(NOT ${CROSS_COMPILER})
    FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/danielbrupaiva/libpqxx.git
        GIT_TAG fbc92684b96c7ae63ebe3ab3bed1bf035af263b6
    )
    FetchContent_MakeAvailable(pqxx)
    FetchContent_GetProperties(pqxx)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC pqxx)
###############################################################################################
