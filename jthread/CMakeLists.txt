set (CMAKE_CXX_STANDARD 20)

project(jthread)
add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    pthread
    fmt::fmt
)
