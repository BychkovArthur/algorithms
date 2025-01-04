cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCE_DIR src)
include_directories(${SOURCE_DIR})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib fmt::fmt)


enable_testing()

add_executable(
  hello_test
  test/tests.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  ${CMAKE_PROJECT_NAME}_lib
)

include(GoogleTest)
gtest_discover_tests(hello_test)