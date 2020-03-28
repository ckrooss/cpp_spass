project(imaginary)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -fno-elide-constructors")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

add_executable(${PROJECT_NAME}
    main.cpp
    include/complex_numbers.h
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
