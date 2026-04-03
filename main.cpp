#include "simulador.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)
    {
        RelojAplicacion::obtenerInstancia(); // Gestión del tiempo para las clases Escribano, Cronometro y Simulador
        Escribano& escribano = Escribano::obtenerInstancia();
        ES_INF("SISTEMA", "Escribano inicializado correctamente.");
        {
            CRONOMETRAR("SISTEMA", "Bloque Principal");
        }
        escribano.mostrarBorrador();
        escribano.cerrarBitacora();
    }
    return 0;
}
