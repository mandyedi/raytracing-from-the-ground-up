cmake_minimum_required(VERSION 3.1)

project(rtf VERSION 1.0
            DESCRIPTION "Ray Tracing from the Ground Up book example project"
            LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(rtf ${SOURCES})

target_include_directories(rtf PRIVATE ${CMAKE_SOURCE_DIR}/src)
