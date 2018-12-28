project(thread_test)

add_compile_options("-fsanitize=thread")
link_libraries("-fsanitize=thread")

add_executable(${PROJECT_NAME}
  src/main.cpp
)
