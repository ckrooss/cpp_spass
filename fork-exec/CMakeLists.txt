project(fork-exec)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_executable(${PROJECT_NAME}-child
    child.cpp
)
