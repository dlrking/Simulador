#ifndef SIMULACION
#define SIMULACION

#include "herramientas/relojPaladin.h"

class Paladin {
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

    long numeroSegundos;
    int numeroMinutos;

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
    std::string mostrarStrFechaInicio();
    std::string mostrarStrFecha();
    std::string mostrarStrFechaFin();


    std::time_t mostrarTiempoFechaInicioPaladin();
    std::time_t mostrarTiempoFechaPaladin();
    std::time_t mostrarTiempoFechaFinPaladin();

    /*
     *
     *
    */
    Paladin();
    /* Destructor de clase.
     */
    ~Paladin();
};

#endif
