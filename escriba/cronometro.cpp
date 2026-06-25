#include "cronometro.h"

Cronometro::Cronometro(const char* origen, const char* funcion, const char* seccion)
    : nombreOrigen(origen), nombreFuncion(funcion), nombreSeccion(seccion) {
    inicio = RelojAplicacion::obtenerCronometro();
}

Cronometro::~Cronometro() {
    std::chrono::steady_clock::time_point fin = RelojAplicacion::obtenerCronometro();
    int64_t duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::string textoDuracion = std::to_string(duracion);
    std::string mensaje = "Función y Tiempo de ejecución en \u00B5s: " + std::string(nombreSeccion) + "," + textoDuracion;
    Escriba::obtenerInstancia().escribirBorrador(nombreOrigen, nivelDeRegistro::DEPURACION, nombreFuncion, mensaje);
}

