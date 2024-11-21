cmake_minimum_required(VERSION 3.28)
project(main CXX)

find_package(fmt REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Weverything)
add_compile_options(-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-weak-vtables -Wno-unsafe-buffer-usage -Wno-padded)
add_compile_options(-fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=undefined)

add_executable(main main.cpp)
target_link_libraries(main fmt::fmt)

find_package(GTest REQUIRED)
add_executable(allocator_test test.cpp)
target_link_libraries(allocator_test fmt::fmt GTest::GTest GTest::Main)