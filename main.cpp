#include "escribano.h"
#include "simulador.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)
    RelojAplicacion::obtenerInstancia();
    return 0;
}
