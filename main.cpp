#include "tecnico.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)
    {
        RelojAplicacion::obtenerInstancia(); // Gestión del tiempo para las clases Escriba, Cronometro y
        Escriba& escribano = Escriba::obtenerInstancia();
        ES_INF("SISTEMA", "Escriba inicializado correctamente.");
        {
            CRONOMETRAR("SISTEMA", "Bloque Principal");
        }
        escribano.mostrarBorrador();
        escribano.cerrarBitacora();
    }
    return 0;
}
