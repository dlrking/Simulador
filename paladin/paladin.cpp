#include "paladin.h"

Paladin::Paladin(const std::string& id, int64_t tiempo, bool interactivo)
: identificador(id), interactivo(interactivo), estado(Estado::Detenido), velocidad(1.0f), reloj(tiempo, 10) {
    std::string mensaje = "Simulación ID: " + identificador + ", Instanciada correctamente.";
    ES_INF(idEscriba, mensaje);
}

Paladin::~Paladin() {
    std::string mensaje = "Simulación ID: " + identificador + ", Destruida correctamente.";
    ES_INF(idEscriba, mensaje);
}

void Paladin::iniciar() {
    estado = Estado::Iniciado;
    ejecutarCiclo();
}

void Paladin::pausar() {
    estado = Estado::Pausado;
}

void Paladin::detener() {
    estado = Estado::Detenido;
    volcarBitacora();
}

void Paladin::ajustarVelocidad(float nuevaVelocidad) {
    velocidad = nuevaVelocidad;
}

void Paladin::actualizar() {
    if (estado == Estado::Iniciado) { reloj.avanzarPaso(); }
}

std::string Paladin::obtenerTextoEstado() const {
    switch(estado) {
        case Estado::Detenido: return "Detenido";
        case Estado::Pausado:  return "Pausado";
        case Estado::Iniciado: return "Iniciado";
        default:               return "Desconocido";
    }
}

void Paladin::volcarBitacora() {
    Escriba::obtenerInstancia().transcribirBorradores();
}

// El método siguiente trabaja virtualmente ad infinitum en modo debug (varios miles de milenios de simulación)
// En la práctica, fuera de debug, una simulación corre máximo 3 milenios virtualmente
#ifndef NDEBUG
void Paladin::ejecutarCiclo() {
    while (estado==Estado::Iniciado) {
        actualizar();
    if(interactivo) {
            // Logica pendiente...
        } else {
            continue; // Puede cambiar, atención
        }
    }
}
#else
void Paladin::ejecutarCiclo() {
    const int64_t miliSegEnTresMilenios = 94670856000000LL;
    while (estado==Estado::Iniciado) {
        int64_t pasoActual = reloj.obtenerPaso()
        // * 10 (minutos de velocidad "base", pendiente modificar para hacer ajustable) * 60 seg * 1000 miliseg;
        if ((pasoActual * 10LL * 60LL * 1000LL) >= miliSegEnTresMilenios) {
            std::string mensaje = "¡Se han simulado tres milenios! Terminando.";
            ES_ADV(idEscriba, mensaje);
            break;
        }
        actualizar();
        if(interactivo) {
            // Logica pendiente...
        } else {
            continue; // Puede cambiar, atención
        }
    }
}
#endif
