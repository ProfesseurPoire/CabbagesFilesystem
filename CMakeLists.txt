cmake_minimum_required(VERSION 3.9.0)

project(CabbagesFilesystem VERSION 1.0.0)

add_subdirectory(modules/Cabbages-test)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_library(${PROJECT_NAME} STATIC
    src/FileSystem.cpp
)

set_property(TARGET CabbagesFilesystem PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:../>)

add_subdirectory(tests/unit)
