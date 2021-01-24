cmake_minimum_required(VERSION 3.1)

project(rtf VERSION 1.0
            DESCRIPTION "Ray Tracing from the Ground Up book example project"
            LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)

# add_executable(rtf ${SOURCES})

# target_include_directories(rtf PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_library(libRTF STATIC ${SOURCES})

add_executable(consoleApp consoleApp.cpp)

target_link_libraries(consoleApp libRTF)

# Unit Test Setup

enable_testing()

add_subdirectory(third_party/googletest-release-1.10.0)

add_subdirectory(test)