#include "tecnico/tecnico.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)
    {
        RelojAplicacion::obtenerInstancia(); // Gestión del tiempo para las el Escriba y el Técnico
        Escriba& escribano = Escriba::obtenerInstancia(); // Inicialización del Escriba
        ES_INF("SISTEMA", "Escriba inicializado correctamente.");
        {
            CRONOMETRAR("SISTEMA", "Bucle Principal");
            {
                ES_INF("SISTEMA", "Iniciando aplicación...");
                CRONOMETRAR("SISTEMA", "Bloque del Técnico");
                {
                    Tecnico tecnico;
                    while (tecnico.estaEjecutando()) {
                        tecnico.ejecutar();
                    }
                    ES_INF("SISTEMA", "Deteniendo aplicación...");
                }
                ES_INF("SISTEMA", "Bloque del Técnico terminado");
            }
            ES_MOSTRAR_BORRADOR();
            ES_INF("SISTEMA", "Bucle Principal finalizado");
        }
        escribano.cerrarBitacora();
    }
    return 0;
}
