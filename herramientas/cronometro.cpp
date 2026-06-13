#include "cronometro.h"

Cronometro::Cronometro(const std::string& objeto, const std::string& funcion, const std::string& seccion)
    : nombreObjeto(objeto), nombreFuncion(funcion), nombreSeccion(seccion) {
    inicio = RelojAplicacion::obtenerCronometro();
}

Cronometro::~Cronometro() {
    std::chrono::steady_clock::time_point fin = RelojAplicacion::obtenerCronometro();
    long duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::string textoDuracion = std::to_string(duracion);
    std::string mensaje = "Función y Tiempo de ejecución en \u00B5s: " + nombreSeccion + "," + textoDuracion;
    Escriba::obtenerInstancia().escribirBorrador(nombreObjeto, nivelDeRegistro::DEPURACION, nombreFuncion, mensaje);
}

