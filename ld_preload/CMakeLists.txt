project(ld_preload)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    good
)


add_library(good SHARED
    lib.cpp
)

add_library(evil SHARED
    evil.cpp
)

set_target_properties(good PROPERTIES VERSION 1.0.0)
set_target_properties(good PROPERTIES PUBLIC_HEADER lib.hpp)
