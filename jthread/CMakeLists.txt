add_executable(jthread
    main.cpp
)

target_link_libraries(jthread
    pthread
    fmt::fmt
)
