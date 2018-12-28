project(slow_copy)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")
set (CMAKE_CXX_INCLUDE_WHAT_YOU_USE /usr/local/opt/llvm/bin/include-what-you-use)

add_executable(${PROJECT_NAME}
    main.cpp
)
