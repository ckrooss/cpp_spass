cmake_minimum_required(VERSION 3.21)
project(testContainer)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_executable(testContainer
    src/main.cpp
    src/container.cpp
    src/item.cpp
)

target_link_libraries(testContainer
  PRIVATE
    GTest::GTest
    GTest::Main
)
enable_testing()
add_test(NAME testContainer COMMAND testContainer)

target_compile_options(testContainer PRIVATE -Wall -Wextra -Wpedantic -Werror)

include_directories(
    include
)