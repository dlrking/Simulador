#include "simulacion.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)

    Simulacion* pSimulacion = new Simulacion();
    delete pSimulacion;

    return 0;
}
