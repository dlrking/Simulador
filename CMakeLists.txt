cmake_minimum_required(VERSION 3.0)

project(sim0)

add_executable(sim0 main.cpp)

install(TARGETS sim0 RUNTIME DESTINATION bin)
