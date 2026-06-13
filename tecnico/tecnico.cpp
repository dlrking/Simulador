#include "tecnico.h"

Tecnico::Tecnico() {

}

Tecnico::~Tecnico() {

}

bool Tecnico::estaEjecutando() {
    return ejecutando;
}

bool Tecnico::configurar(std::string, std::string) {

}

void Tecnico::ejecutar() {

}

std::string Tecnico::verificarTextoFecha(const std::string&) {

}

std::chrono::system_clock Tecnico::convertirTextoFechaEnInstante(const std::string&) {

}

bool Tecnico::validarRangoFechas(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point) {

}
