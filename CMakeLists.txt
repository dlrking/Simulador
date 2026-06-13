cmake_minimum_required(VERSION 3.0)

project(sim0)

add_executable(sim0
               main.cpp
               escriba/herramientas/encabezados.h
               escriba/herramientas/relojAplicacion.cpp
               escriba/escriba.cpp
               escriba/cronometro.cpp
               paladin/paladin.cpp
               paladin/herramientas/relojPaladin.cpp
               tecnico/tecnico.cpp)

install(TARGETS sim0 RUNTIME DESTINATION bin)
