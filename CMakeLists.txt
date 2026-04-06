cmake_minimum_required(VERSION 3.0)

project(sim0)

add_executable(sim0
               main.cpp
               herramientas/encabezados.h
               herramientas/relojAplicacion.cpp
               herramientas/escribano.cpp
               herramientas/cronometro.cpp
               simulacion/simulacion.cpp
               simulacion/herramientas/relojSimulacion.cpp
               simulador.cpp)

install(TARGETS sim0 RUNTIME DESTINATION bin)
