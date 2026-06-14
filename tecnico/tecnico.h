#ifndef TECNICO
#define TECNICO

#include "../paladin/paladin.h"

class Tecnico {
public:
    Tecnico();
    ~Tecnico();

    static constexpr const char* idEscriba = "TECNICO";

    bool estaEjecutando();
    bool configurar(std::string, std::string);

    void ejecutar();

private:
    std::string textoFecha;
    std::string textoFechaSistema;

    std::chrono::system_clock::time_point instanteInicial;
    std::chrono::system_clock::time_point instante;

    long duracionSegundos;
    long duracionMinutos;

    std::vector<std::unique_ptr<Paladin>> simulaciones;
    Paladin* simulacionInteractiva;

    bool ejecutando;

    std::string textoTarea;

    int semillaAleatoria;

    std::string verificarTextoFecha(const std::string&);
    std::chrono::system_clock convertirTextoFechaEnInstante(const std::string&);
    bool validarRangoFechas(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);


};

#endif
