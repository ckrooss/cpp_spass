project(lohmann_unicode)
add_executable(lohmann_unicode main.cpp)
target_link_libraries(lohmann_unicode nlohmann_json::nlohmann_json)

file(COPY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/testfile ${CMAKE_CURRENT_BINARY_DIR}/testfile)