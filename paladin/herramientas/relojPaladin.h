#ifndef RELOJ_SIMULACION
#define RELOJ_SIMULACION

#include "../../escriba/herramientas/encabezados.h"

// Estructura de tiempo para las entidades que necesiten alguna "idea" de la fecha y la hora
struct FechaHora {
    int año;
    int mes;
    int diaMes;
    int diaSemana; // 0 (Domingo) a 6 (Sábado)
    int hora;
    int minuto;
    int segundo;
    std::string texto; // "YYYY-MM-DD HH:MM:SS"
};

class RelojP {
public:
    RelojP (long, int);

    void avanzarPaso(); // Avanza un paso de la simulación
    // Obtenedores y ajustadores
    long obtenerPaso() const { return paso; }
    const FechaHora& obtenerFechaHora() const { return fechaHora; }
    void ajustarResolucion(int nuevaResolucion) { resolucion = nuevaResolucion; }

private:

    long paso; // El número de pasos que ha hecho la simulación
    long tiempoSistema; // Fecha y hora del sistema al inicio de la simulación
    int resolucion; // La resolución indica el número de minutos de simulación por cada paso
    FechaHora fechaHora; // Fecha y hora de la simulación/al interior de la simulación
    void actualizarFechaHora(); // Actualiza la fecha y hora según el número de paso
};

#endif
