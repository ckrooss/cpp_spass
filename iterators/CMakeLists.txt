cmake_minimum_required(VERSION 3.21)
project(testContainer CXX)

#find_package(GTest REQUIRED)
include(FetchContent)
FetchContent_Declare(
  GTest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
FetchContent_MakeAvailable(GTest)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_executable(testContainer
    src/main.cpp
    src/container.cpp
    src/item.cpp
)

target_link_libraries(testContainer
  PRIVATE
    gtest
    gtest_main
)
enable_testing()
add_test(NAME testContainer COMMAND testContainer)

target_compile_options(testContainer PRIVATE -Wall -Wextra -Wpedantic -Werror)

include_directories(
    include
)
