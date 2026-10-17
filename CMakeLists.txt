cmake_minimum_required(VERSION 3.31)
project(Project)

enable_testing()
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-fexperimental-library)
endif()

# ASAN
#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

add_compile_options(-Wall -Wextra -Werror)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#12.2.0")
CPMAddPackage("gh:nlohmann/json@3.12.0")
CPMAddPackage("gh:catchorg/Catch2@3.16.0")
CPMAddPackage("gh:google/googletest@1.18.0")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.4.0")
CPMAddPackage("gh:gsl-lite/gsl-lite@1.1.1")
CPMFindPackage(
        NAME mp-units
        VERSION 2.6.0
        GIT_TAG 7de22b0de37eceb4037594f2f2800ef3957738f9
        GITHUB_REPOSITORY mpusz/mp-units
        SOURCE_SUBDIR src
        SYSTEM YES
        EXCLUDE_FROM_ALL YES
        OPTIONS
        "MP_UNITS_BUILD_INSTALL OFF"
        "MP_UNITS_USE_LIBFMT ON"
#        "MP_UNITS_BUILD_CXX_MODULES ON"
)

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
add_subdirectory(slow_copy)
add_subdirectory(mp-units-examples)
