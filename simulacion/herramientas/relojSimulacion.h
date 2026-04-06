#ifndef RELOJ_SIMULACION
#define RELOJ_SIMULACION

#include "../../herramientas/encabezados.h"

// Decomposed time for entity awareness
struct FechaHoraSimulacion {
    int año;
    int mes;
    int diaMes;
    int diaSemana; // 0 (Sun) to 6 (Sat)
    int hora;
    int minuto;
    int segundo;
    std::string texto; // "YYYY-MM-DD HH:MM:SS"
};

class RelojSimulacion {
public:
    // inicioUnix: Anchor point (e.g., 1712160000 for April 2024)
    // resolucionSegundos: How many virtual seconds pass per tick
    RelojSimulacion(long inicioUnix, int resolucionSegundos = 1);

    // The Master Heartbeat: Advances the virtual world
    void avanzarTick();

    // Getters (Sober & Explicit)
    long obtenerTickActual() const { return tickActual; }
    const FechaHoraSimulacion& obtenerFechaActual() const { return fechaActual; }

private:
    long tickActual;
    long anclaUnix;
    int resolucion;

    FechaHoraSimulacion fechaActual;

    // Self-contained logic: Updates the POD from the internal counter
    void actualizarFechaVirtual();
};

#endif
