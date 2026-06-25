#include "tecnico/tecnico.h"

namespace SeñalSistema {
    volatile std::sig_atomic_t solicitarCierre = 0;

    void interpretarSeñal(int señal) {
        if (señal == SIGINT || señal == SIGTERM) { solicitarCierre = 1; }
    }

    void registrarSeñal() {
        std::signal(SIGINT, interpretarSeñal);
        std::signal(SIGTERM, interpretarSeñal);
    }
}

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)
    {
        RelojAplicacion::obtenerInstancia(); // Gestión del tiempo para las el Escriba y el Técnico
        Escriba& escribano = Escriba::obtenerInstancia(); // Inicialización del Escriba
        ES_INF("SISTEMA", "Escriba inicializado correctamente.");
        SeñalSistema::registrarSeñal();
        ES_DEP("SISTEMA", "Controlador de eventos del sistema iniciado.");
        while(!SeñalSistema::solicitarCierre) {
            CRONOMETRAR("SISTEMA", "bucle principal (main)");
        }
        escribano.cerrarBitacora();
    }
    return 0;
}
