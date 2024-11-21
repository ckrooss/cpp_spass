cmake_minimum_required(VERSION 3.31)
project(Project)

enable_testing()
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
    GIT_TAG           11.0.2
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmt
    SUBBUILD_DIR      third_party/fmt/subbuild
    BINARY_DIR        third_party/fmt/build
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           v1.15.2
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest
    SUBBUILD_DIR      third_party/googletest/subbuild
    BINARY_DIR        third_party/googletest/build
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(catch2
    GIT_REPOSITORY    https://github.com/catchorg/Catch2.git
    GIT_TAG           v3.7.1
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2
    SUBBUILD_DIR      third_party/catch2/subbuild
    BINARY_DIR        third_party/catch2/build
)
FetchContent_MakeAvailable(catch2)

FetchContent_Declare(njson
    GIT_REPOSITORY    https://github.com/nlohmann/json.git
    GIT_TAG           v3.11.3
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/nlohmann_json
    SUBBUILD_DIR      third_party/nlohmann_json/subbuild
    BINARY_DIR        third_party/nlohmann_json/build
)
FetchContent_MakeAvailable(njson)


# ASAN
#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-fno-rtti -fno-exceptions -O2)

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
