cmake_minimum_required(VERSION 3.5)

project(GS_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories("../")

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

file(GLOB TARGET_SOURCES "../*.cpp")
list(FILTER TARGET_SOURCES EXCLUDE REGEX ".*main.cpp$")
file(GLOB TARGET_HEADERS "../*.h")

add_executable(runUnitTests
    ${SOURCES}
    ${HEADERS}
    ${TARGET_SOURCES}
    ${TARGET_HEADERS}
)

target_link_libraries(runUnitTests GTest::GTest)

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)

