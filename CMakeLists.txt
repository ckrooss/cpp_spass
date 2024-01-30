cmake_minimum_required(VERSION 3.7)
project(Project)

add_subdirectory(Catch2)

enable_testing()
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# ASAN
#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-fno-rtti -fno-exceptions -march=native -mtune=native -O3)

add_subdirectory(jthread)
add_subdirectory(Threads)
add_subdirectory(Visitor)
add_subdirectory(address_sanitizer)
add_subdirectory(cond_var)
add_subdirectory(fork-exec)
add_subdirectory(imaginary)
add_subdirectory(ld_preload)
add_subdirectory(predict)
add_subdirectory(sqlite)
add_subdirectory(template_class)
add_subdirectory(modules)
add_subdirectory(pimpl)
add_subdirectory(unit_types)
add_subdirectory(lohmann_unicode)
