cmake_minimum_required(VERSION 3.23)
project(VehicleProject)

include_directories(include src)
set(CMAKE_CXX_STANDARD 11)

add_executable(VehicleProject src/main.cpp src/Vehicle.cpp include/Vehicle.h src/Path.cpp include/Path.h src/Steering.cpp include/Steering.h include/defines.h)
