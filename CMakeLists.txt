cmake_minimum_required(VERSION 3.0)

project(sim0)

add_executable(sim0 main.cpp relojAplicacion.cpp escribano.cpp simulador.cpp simulacion.cpp)

install(TARGETS sim0 RUNTIME DESTINATION bin)
