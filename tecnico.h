#ifndef SIMULADOR
#define SIMULADOR

#include "herramientas/cronometro.h"
#include "paladin/paladin.h"


class Tecnico {
public:
    Tecnico();
    ~Tecnico();

    static constexpr const char* idEscriba = "SIMULADOR";

    bool configurar(std::string, std::string);

    void ejecutar();

private:
    std::string textoFecha;
    std::string textoFechaSistema;

    std::chrono::system_clock::time_point tiempoInicial;
    std::chrono::system_clock::time_point tiempoFinal;
    long duracionSegundos;
    long duracionMinutos;

    Paladin simulacion;

    bool ejecutando;
    std::string textoEstado;

    int semillaAleatoria;

    std::string verificarTextoFecha(const std::string&);
    std::chrono::system_clock convertirTextoFechaEnTiempo(const std::string&);
    bool validarRangoFechas(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);


};

#endif
