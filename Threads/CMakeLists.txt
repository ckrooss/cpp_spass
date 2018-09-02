cmake_minimum_required(VERSION 3.11)
project(main)
set (CMAKE_CXX_STANDARD 14)

# cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# clang-tidy -p="." ../src/*.cpp -checks='*,-clang-analyzer-alpha.*' -fix
# clang-format --style=llvm -i include/*.h src/*.cpp
add_compile_options("-fsanitize=thread")
link_libraries("-fsanitize=thread")

add_executable(main
  src/main.cpp
)
