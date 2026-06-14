#ifndef RELOJ_PALADIN
#define RELOJ_PALADIN

#include "../../escriba/cronometro.h"

// Estructura de tiempo para las entidades que necesiten alguna "idea" de la fecha y la hora
struct FechaHora {
    int año;
    int mes;
    int diaMes;
    int diaSemana; // 0 (Domingo) a 6 (Sábado)
    int hora;
    int minuto;
    int segundo;
    bool feriado;
    std::string texto; // "YYYY/MM/DD,HH:MM:SS"
};

class RelojP {
public:
    RelojP(unsigned long long, int);

    void avanzarPaso(); // Avanza un paso discreto de la simulación (ms)
    // Obtenedores y ajustadores
    unsigned long long obtenerPaso() const { return paso; }
    const FechaHora& obtenerFechaHora() const { return fechaHora; }
    void ajustarResolucion(int nuevaResolucion) { resolucion = nuevaResolucion; }

private:

    unsigned long long paso; // El número de pasos que ha hecho la simulación
    unsigned long long tiempoSistema; // Fecha y hora del sistema al inicio de la simulación
    int resolucion; // La resolución indica el número de minutos de simulación por cada paso
    FechaHora fechaHora; // Fecha y hora de la simulación/al interior de la simulación

    std::set<std::string> feriados;

    void actualizarFechaHora(); // Actualiza la fecha y hora según el número de paso
    bool esBisiesto(int año) const { return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0); } // Verifica si el año en curso es bisiesto o no
    int obtenerDiasDelMes(int, int) const; // Obtiene el número de días que le corresponden al mes
};

#endif
