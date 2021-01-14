cmake_minimum_required(VERSION 3.1)

file(GLOB_RECURSE TEST_SOURCES ./*.cpp)

add_executable(runTest ${TEST_SOURCES})

target_link_libraries(runTest PUBLIC
	gtest_main
	libRTF
)

add_test(runTest runTest)