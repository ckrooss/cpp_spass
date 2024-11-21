project(thread_test)

add_executable(thread_test
  src/main.cpp
)

target_link_libraries(thread_test PRIVATE atomic)