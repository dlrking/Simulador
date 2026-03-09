#ifndef _SIMULACION
#define _SIMULACION

#include "simulador.h"
#include "objetos.h"

class Simulacion {
friend class Simulador;
private:
    // Atributos
    std::string strFechaInicial;
    std::string strFechaActual;
    std::string strFechaFinal;
    std::string strFechaSistema;

    std::tm tmFechaInicial;
    std::tm tmFechaActual;
    std::tm tmFechaFinal;
    std::tm tmFechaSistema;

    std::time_t tiempoFechaInicial;
    std::time_t tiempoFechaActual;
    std::time_t tiempoFechaFinal;
    std::time_t tiempoFechaSistema;

    int tiempoSimulacionSegundos;
    int tiempoSimulacionMinutos;

    std::vector<std::tm> vectorTiempo;

    // Métodos
    void inicializarFechaTransferencia();
    void obtenerFecha();
    void comprobarFormatoFecha();
    void comprobarValidezFecha();
    void ajustarFecha(std::string);
    void comprobarIntervaloFecha();
    std::vector<std::tm> inicializarVectorTiempo();

public:
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

    /* Constructor de clase.
     * Usualmente público o protegido.
     * Puede ser privado en ciertos patrones de diseño (singleton).
    */
    Simulacion();
    /* Destructor de clase.
     */
    ~Simulacion();
};

#endif
