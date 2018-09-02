cmake_minimum_required(VERSION 3.11)
project(visitor_test)
set (CMAKE_CXX_STANDARD 14)

# cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# clang-tidy -p="." ../src/*.cpp -checks='*,-clang-analyzer-alpha.*' -fix
# clang-format --style=llvm -i include/*.h src/*.cpp
add_compile_options("-fsanitize=address")
link_libraries("-fsanitize=address")

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/Visitor.cpp
  src/Bilanzposten.cpp
)

include_directories(include)
