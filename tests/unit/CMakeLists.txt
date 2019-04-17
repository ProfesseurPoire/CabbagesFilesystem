cmake_minimum_required(VERSION 3.9.0)

project(Test_Unit_Filesystem)

#Tests need Cabbages-test package
find_package(cabbages-test 1.0 CONFIG REQUIRED)

if(NOT TARGET cabbages-test)
    message("Could not found cabbages-test")
else()
    message("Cabbages-test founded")
endif()


add_executable(${PROJECT_NAME}
    main.cpp
    UTFileSystem.cpp
)
 
target_link_libraries(${PROJECT_NAME}
    cabbages-test
    CabbagesFilesystem
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

add_test( NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})