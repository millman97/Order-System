cmake_minimum_required(VERSION 3.13)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

project(billingSys)

#Get GoogleTest
include(FetchContent)
FetchContent_Declare(googleTest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.12.1)

FetchContent_GetProperties(googleTest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()


add_library(shoppingLib STATIC shopping.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp shoppingLib)

add_executable(runTest test.cpp)
target_link_libraries(runTest shoppingLib gtest_main gmock_main)

