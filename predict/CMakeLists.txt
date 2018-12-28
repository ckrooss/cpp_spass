project(predict)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -ffast-math")

add_executable(${PROJECT_NAME}
    main.cpp
)
