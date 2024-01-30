project(modules)

add_executable(main
    src/main.cpp
    src/MyClass.cpp
)

target_include_directories(main
    PUBLIC
    include
)