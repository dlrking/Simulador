#ifndef SIMULADOR
#define SIMULADOR

#include "simulacion.h"

class Simulador {
public:
    Simulador();
    ~Simulador();

    bool configurar(std::string, std::string);

    void ejecutar();

    static std::chrono::system_clock::time_point obtenerTiempoSistema() { return tiempoSistema; }
    static std::chrono::steady_clock::time_point obtenerTiempoCronometro() { return tiempoCronometro; }

private:
    std::string textoFechaSimulacion;
    std::string textoFechaSistema;

    static inline std::chrono::system_clock::time_point tiempoSistema;
    static inline std::chrono::steady_clock::time_point tiempoCronometro;

    std::chrono::system_clock::time_point tiempoInicial;
    std::chrono::system_clock::time_point tiempoFinal;
    long duracionSegundos;
    long duracionMinutos;

    Simulacion simulacion;

    bool ejecutando;
    std::string textoEstado;

    int semillaAleatoria;

    std::string verificarTextoFecha(const std::string&);
    std::chrono::system_clock convertirTextoFechaEnTiempo(const std::string&);
    bool validarRangoFechas(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);


};

#endif
