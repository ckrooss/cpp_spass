project(imaginary)

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

    target_link_libraries(catch-testcases pthread Catch2::Catch2WithMain)
    target_include_directories(catch-testcases PUBLIC include /usr/local/include/)
    add_test(NAME catch-testcases COMMAND catch-testcases)

endif(CMAKE_TESTING_ENABLED)
