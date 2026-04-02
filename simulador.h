#ifndef SIMULADOR
#define SIMULADOR

#include "simulacion.h"
#include "relojAplicacion.h"

class Simulador {
public:
    Simulador();
    ~Simulador();

    bool configurar(std::string, std::string);

    void ejecutar();

private:
    std::string textoFechaSimulacion;
    std::string textoFechaSistema;

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
