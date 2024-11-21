project(imaginary)

add_executable(${PROJECT_NAME}
    main.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_library(imaginary-catch-main
    tests/catch_main.cpp
)

add_executable(imaginary-catch
    tests/imaginary_catch.cpp
)

add_executable(imaginary-gtest
    tests/gtest_main.cpp
    tests/imaginary_gtest.cpp
)

find_package(GTest REQUIRED)
target_link_libraries(imaginary-catch pthread imaginary-catch-main)
target_link_libraries(imaginary-gtest pthread GTest::gtest)
