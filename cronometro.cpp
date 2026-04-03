#include "cronometro.h"

Cronometro::Cronometro(const std::string& objeto, const std::string& funcion, const std::string& seccion) {
    nombreObjeto = objeto;
    nombreFuncion = funcion;
    nombreSeccion = seccion;
    inicio = RelojAplicacion::obtenerTiempoDelCronometro();
}

Cronometro::~Cronometro() {
    std::chrono::steady_clock::time_point fin = RelojAplicacion::obtenerTiempoDelCronometro();
    long intDuracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::string textoDuracion = std::to_string(intDuracion);
    std::string mensaje = "Función y Tiempo de ejecución en \u00B5s: " + nombreSeccion + "," + textoDuracion;
    Escribano::obtenerInstancia().escribirBorrador(nombreObjeto, nivelDeRegistro::DEPURACION, nombreFuncion, mensaje);
}

