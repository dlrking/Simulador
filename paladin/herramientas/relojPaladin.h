#ifndef RELOJ_PALADIN
#define RELOJ_PALADIN

#include "../../escriba/cronometro.h"

class RelojP {
public:
    static constexpr const char* idEscriba = "RELOJ PALADIN";

    RelojP(int64_t, int);

    void avanzarPaso(); // Avanza un paso discreto de la simulación (resolucion en unidades de tiempo por paso)

    // Obtenedores y ajustadores
    std::string obtenerDiaSemana() const;
    int64_t obtenerPaso() const { return paso; }
    const FechaHora& obtenerFechaHora() const { return fechaHora; }
    void ajustarResolucion(int);

private:
    int64_t paso; // El número de pasos que ha hecho la simulación
    int64_t tiempoSistema; // Fecha y hora del sistema al inicio de la simulación
    int resolucion; // La resolución indica el número de minutos de simulación por cada paso
    FechaHora fechaHora; // Fecha y hora de la simulación/al interior de la simulación

    std::set<std::string> feriados;

    void actualizarFechaHora(); // Actualiza la fecha y hora según el número de paso
    int obtenerDiasDelMes(int, int) const; // Obtiene el número de días que le corresponden al mes
};

#endif
