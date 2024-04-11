cmake_minimum_required(VERSION 3.10)
project(RB-tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g -rdynamic)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(TEST_DIR test)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

enable_testing()
find_package(GTest REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)

add_test(AllTestsInFoo foo)

# add_executable(${CMAKE_PROJECT_NAME}_exe ${SOURCE_DIR}/rb.cpp)

