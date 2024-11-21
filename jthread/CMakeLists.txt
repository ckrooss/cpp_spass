set (CMAKE_CXX_STANDARD 20)

project(jthread)
add_compile_options(-fsanitize=thread)
add_link_options(-fsanitize=thread)
add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    pthread
    fmt::fmt
)
