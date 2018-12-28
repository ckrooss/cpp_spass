cmake_minimum_required(VERSION 3.12)
project(imaginary)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -fno-elide-constructors")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

enable_testing()

add_executable(${PROJECT_NAME}
    main.cpp
    include/complex.h
)

include_directories(
    /usr/local/include/
    include
)


if(CMAKE_TESTING_ENABLED)
    add_executable(catch-testcases
         tests/imaginary_catch.cpp
    )

    add_library(catch-main SHARED
        tests/catch_main.cpp
    )

    target_link_libraries(catch-testcases pthread catch-main)

    target_include_directories(catch-testcases PUBLIC include /usr/local/include/)
    target_include_directories(catch-main PUBLIC include /usr/local/include/)

endif(CMAKE_TESTING_ENABLED)

if(0)
    add_executable(gtest-test
        tests/main.cpp
        tests/imaginary.cpp
    )
    target_link_libraries(gtest-test gtest pthread)
    target_include_directories(gtest-test PUBLIC include /usr/local/include/)
endif()
