add_executable(mpu
        main.cpp
)

target_link_libraries(mpu
  PRIVATE
    mp-units::mp-units
)

