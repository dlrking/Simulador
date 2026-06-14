cmake_minimum_required(VERSION 3.0)

project(sim0)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

add_executable(sim0
               main.cpp
               escriba/herramientas/encabezados.h
               escriba/herramientas/relojAplicacion.cpp
               escriba/escriba.cpp
               escriba/cronometro.cpp
               paladin/herramientas/relojPaladin.cpp
               paladin/paladin.cpp
               tecnico/herramientas/consola.cpp
               tecnico/tecnico.cpp)

target_include_directories(sim0 PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(sim0 PRIVATE ${CURSES_LIBRARIES})

install(TARGETS sim0 RUNTIME DESTINATION bin)
