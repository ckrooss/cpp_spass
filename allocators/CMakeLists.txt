project(main CXX)
add_executable(allocator main.cpp)
target_link_libraries(allocator fmt::fmt)
