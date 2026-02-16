cmake_minimum_required(VERSION 3.22)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mc_dingo)
set(PROJECT_DESCRIPTION "dingo robot module for mc_rtc")

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.0)
include(CTest)
enable_testing()

find_package(mc_rtc REQUIRED)
find_description_package(dingo_description REQUIRED)

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
