cmake_minimum_required(VERSION 3.9.0)

project(Test_Unit_Filesystem)

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