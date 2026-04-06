#ifndef SIMULACION
#define SIMULACION

#include "herramientas/relojSimulacion.h"

class Simulacion {
public:

    std::string strFecha;

    std::tm tmFechaInicial;
    std::tm tmFechaActual;
    std::tm tmFechaFinal;
    std::tm tmFechaSistema;

    std::time_t tiempoInicial;
    std::time_t tiempoActual;
    std::time_t tiempoFinal;
    std::time_t tiempoSistema;

    long tiempoSimulacionSegundos;
    int tiempoSimulacionMinutos;

    std::vector<std::tm> vectorTiempo;

    // Métodos
    void inicializarFechaTransferencia();
    void obtenerFecha();
    void comprobarFormatoFecha();
    void comprobarValidezFecha();
    void ajustarFecha(std::string);
    void comprobarIntervaloFecha();
    void inicializarVectorTiempo();

    // Atributos
    std::string strFechaTransferencia;
    std::tm tmFechaTransferencia;
    std::time_t tiempoFechaTransferencia;

    // Métodos
    std::string mostrarStrFechaInicioSimulacion();
    std::string mostrarStrFechaSimulacion();
    std::string mostrarStrFechaFinSimulacion();

    std::time_t mostrarTiempoFechaInicioSimulacion();
    std::time_t mostrarTiempoFechaSimulacion();
    std::time_t mostrarTiempoFechaFinSimulacion();

    /*
     *
     *
    */
    Simulacion();
    /* Destructor de clase.
     */
    ~Simulacion();
};

#endif
