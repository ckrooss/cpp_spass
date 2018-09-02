project(c++_spass)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -fPIC -fPIE -pie)

add_executable(main main.cpp)

target_link_libraries(main sqlite3)
