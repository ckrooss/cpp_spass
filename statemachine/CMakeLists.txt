cmake_minimum_required(VERSION 3.23)
project(statemachine)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-fsanitize=address")
add_compile_options("-O2")
link_libraries("-fsanitize=address")

add_executable(${PROJECT_NAME}
    sm.cpp
    main.cpp
)
