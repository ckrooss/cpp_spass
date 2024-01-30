project(visitor_test)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/Visitor.cpp
  src/Bilanzposten.cpp
)

include_directories(include)
