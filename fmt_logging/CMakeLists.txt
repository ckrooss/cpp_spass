project(fmtlog)
add_executable(${PROJECT_NAME}
    main.cpp
    fmtlog.cpp
    #fmtlog_syslog.cpp
)
target_link_libraries(${PROJECT_NAME} fmt::fmt)