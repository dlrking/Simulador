cmake_minimum_required(VERSION 3.0)

project(sim0)

add_executable(sim0
               main.cpp
               herramientas/encabezados.h
               herramientas/relojAplicacion.cpp
               herramientas/escriba.cpp
               herramientas/cronometro.cpp
               paladin/paladin.cpp
               paladin/herramientas/relojPaladin.cpp
               tecnico.cpp)

install(TARGETS sim0 RUNTIME DESTINATION bin)
