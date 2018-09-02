cmake_minimum_required(VERSION 3.11)
project(c++_spass)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# set (CMAKE_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


add_executable(main
    main.cpp
)

target_link_libraries(main good)


add_library(good SHARED
    lib.cpp
)

add_library(evil SHARED
    evil.cpp
)

set_target_properties(good PROPERTIES VERSION 1.0.0)
set_target_properties(good PROPERTIES PUBLIC_HEADER lib.hpp)
