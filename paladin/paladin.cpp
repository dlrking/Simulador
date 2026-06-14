#include "paladin.h"

Paladin::Paladin(const std::string& id, unsigned long long tiempo, bool interactivo) :
 reloj(tiempo, 10) {

}

Paladin::~Paladin() {}

void Paladin::iniciar() {}
void Paladin::pausar() {}
void Paladin::detener() {}
void Paladin::ajustarVelocidad() {}

void Paladin::actualizar() {}

std::string Paladin::obtenerTextoEstado() const {}
