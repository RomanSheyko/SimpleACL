cmake_minimum_required(VERSION 3.5)

project(NokiaTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(WITH_TESTS "Build unit tests" OFF)

find_package(rapidjson)
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
include_directories(${RAPIDJSON_INCLUDE_DIRS})

if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)

add_executable(NokiaTest ${SOURCES} ${HEADERS})
