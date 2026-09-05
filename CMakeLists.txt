cmake_minimum_required(VERSION 3.31)
project(Project)

enable_testing()
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
    GIT_TAG           758d39eb239e6554d3ac0659b6f592fcd5317c24
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmt
    BINARY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmt/build
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           v1.15.2
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest
    BINARY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/build
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(catch2
    GIT_REPOSITORY    https://github.com/catchorg/Catch2.git
    GIT_TAG           v3.15.1
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2
    BINARY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2/build
)
FetchContent_MakeAvailable(catch2)

FetchContent_Declare(njson
    GIT_REPOSITORY    https://github.com/nlohmann/json.git
    GIT_TAG           v3.12.0
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/nlohmann_json
    BINARY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/nlohmann_json/build
)
FetchContent_MakeAvailable(njson)

FetchContent_Declare(SQLiteCpp
    GIT_REPOSITORY    https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG           master
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SQLiteCpp
    BINARY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SQLiteCpp/build
)
FetchContent_MakeAvailable(SQLiteCpp)


if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
add_compile_options(-fexperimental-library)
endif()

# ASAN
#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

add_compile_options(-Wall -Wextra -Werror)
add_compile_options(-fno-rtti -Os -flto=thin)

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
add_subdirectory(custom_float_types)
add_subdirectory(fmt_logging)
add_subdirectory(syslog)
add_subdirectory(allocators)
add_subdirectory(statemachine)
