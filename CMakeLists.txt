cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
find_package(aws-sdk-cpp)
add_definitions(-DUSE_IMPORT_EXPORT)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test_s3.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
