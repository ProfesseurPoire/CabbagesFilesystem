cmake_minimum_required(VERSION 3.9.0)

project(CabbagesFilesystem VERSION 1.0.0)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)

add_library(${PROJECT_NAME} STATIC
    src/FileSystem.cpp
)

set_property(TARGET CabbagesFilesystem PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_subdirectory(tests/unit)


#####################################################
# Installing the library and exporting the targets
#####################################################

# We'll install the library in lib64 if we're in x64, in lib otherwise

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(arch_suffix "")
else()
    set(arch_suffix "64")
endif()

set(library_install_directory "lib${arch_suffix}")

include(CMakePackageConfigHelpers)

# Creates the config-version file that cmake uses to know if
# if package pulled by the find_package function is compatible
# depending on the version asked by the find_package function
write_basic_package_version_file(
    ${PROJECT_NAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

# So I guess this just tell Cmake that the name of the exported
# target will be ${PROJECT_NAME}-target, and associates the path
# on where to find the include,library,archive etc
install(
    TARGETS     ${PROJECT_NAME}     
    EXPORT      ${PROJECT_NAME}-target      #Associates the installed target files with an export thing
    LIBRARY     DESTINATION ${library_install_directory}/${CMAKE_BUILD_TYPE}
    ARCHIVE     DESTINATION ${library_install_directory}/${CMAKE_BUILD_TYPE}
    RUNTIME     DESTINATION ${library_install_directory}/${CMAKE_BUILD_TYPE}
    INCLUDES    DESTINATION include)

# Generates and install a cmake file containing code to import targets
# from the installation tree into another project
#
# A install(targets x export y) must exist beforehand
#
install(
    EXPORT  ${PROJECT_NAME}-target
    FILE    ${PROJECT_NAME}-target.cmake
    DESTINATION ${library_install_directory}/cmake/${PROJECT_NAME}
)

configure_file(cmake/config.cmake.in ${PROJECT_NAME}-config.cmake @ONLY)

# Installs the config and config version file 
install(
    FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"  
    DESTINATION ${library_install_directory}/cmake/${PROJECT_NAME}
)

# Installing header files
install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN *.h)