project(imaginary)

add_executable(${PROJECT_NAME}
    main.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(imaginary-catch
    tests/imaginary_catch.cpp
)

add_executable(imaginary-gtest
    tests/imaginary_gtest.cpp
)

target_link_libraries(imaginary-catch pthread Catch2::Catch2WithMain)
target_link_libraries(imaginary-gtest pthread GTest::gtest_main)
