#include "simulador.h"

Simulador::Simulador() {
    tiempoSistema    = std::chrono::system_clock::now();
    tiempoCronometro = std::chrono::steady_clock::now();
}
