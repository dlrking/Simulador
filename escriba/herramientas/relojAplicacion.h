#ifndef RELOJ_APLICACION
#define RELOJ_APLICACION

#include "encabezados.h"

// Estructura de tiempo para las entidades que necesiten alguna "idea" de la fecha y la hora
struct FechaHora {
    int año;
    int mes;
    int diaAño;         // 1-366 (se considera el año bisiesto)
    int diaMes;         // 1-31
    int diaSemana;      // 0 Dom, 1 Lun, 2 Mar...
    int semanaAño;      // 1-53 (52.1xxx semanas por año, techo)
    int semanaMes;      // 1-5
    int hora;
    int minuto;
    int segundo;
    int milisegundo;    // 1-999
    std::string texto;  // "YYYY/MM/DD,HH:MM:SS"
    std::string dia;    // Lunes, Martes...
};

class RelojAplicacion {
public:
    static RelojAplicacion& obtenerInstancia();
    static std::chrono::system_clock::time_point obtenerInstanteInicial() { return tiempoInicial; }
    static std::chrono::system_clock::time_point obtenerInstanteActual() { return std::chrono::system_clock::now(); }
    static std::chrono::steady_clock::time_point obtenerCronometro() { return std::chrono::steady_clock::now(); }

    static int64_t textoFechaEnMiliseg(const std::string);
    static std::string milisegEnTextoFecha(int64_t);

    static FechaHora obtenerFechaHora(int64_t);

private:
    // Sólo puede haber un objeto de esta clase así que modificamos operadores (=) (prevención de duplicados)
    RelojAplicacion(const RelojAplicacion&) = delete;
    RelojAplicacion& operator=(const RelojAplicacion&) = delete;

    static inline std::chrono::system_clock::time_point tiempoInicial;

    static bool esBisiesto(int año) { return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0); }
    static int diasDelMes(int, int);

    RelojAplicacion() { tiempoInicial = std::chrono::system_clock::now(); }
    ~RelojAplicacion() = default;
};

#endif
