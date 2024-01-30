project(modules)

add_executable(run
    run.cpp)

add_library(modA
    SHARED
    modA.cpp
)

add_library(modB
    SHARED
    modB.cpp
)

target_link_libraries(run
    dl
)