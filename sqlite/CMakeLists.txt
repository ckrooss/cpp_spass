project(sqlite_test)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    SQLiteCpp
    sqlite3
)

target_compile_options(${PROJECT_NAME} PUBLIC -fexceptions)