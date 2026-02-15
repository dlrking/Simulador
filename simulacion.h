#ifndef _SIMULACION
#define _SIMULACION
#include "encabezados.h"
#include "objetos.h"

class Simulacion {
public:
    // Atributos (públicos)
    std::string strFechaTransferenciaSimulacion;
    std::tm tmFechaTransferenciaSimulacion;
    // Métodos/funciones (públicas) de clase
    // Constructor de clase
    Simulacion();
    ~Simulacion();
    //
    void obtenerStrFechaInicioSimulacion();
    void obtenerStrFechaSimulacion();
    void obtenerStrFechaFinSimulacion();
    //
    void ajustarStrTmFechaInicioSimulacion();
    void ajustarStrTmFechaSimulacion();
    void ajustarStrTmFechaFinSimulacion();
    //
    std::string mostrarStrFechaInicioSimulacion();
    std::string mostrarStrFechaSimulacion();
    std::string mostrarStrFechaFinSimulacion();
private:
    // Atributos (privados)
    std::string strFechaInicioSimulacion;
    std::string strFechaSimulacion;
    std::string strFechaFinSimulacion;
    //
    std::tm tmFechaInicioSimulacion;
    std::tm tmFechaSimulacion;
    std::tm tmFechaFinSimulacion;
    //
    std::time_t tiempoFechaInicioSimulacion;
    std::time_t tiempoFechaSimulacion;
    std::time_t tiempoFechaFinSimulacion;
    // Métodos/funciones (privadas) de clase
    std::time_t obtenerTiempoFechaInicioSimulacion();
    std::time_t obtenerTiempoFechaSimulacion();
    std::time_t obtenerTiempoFechaFinSimulacion();
    //
    void ajustarTiempoFechaInicioSimulacion();
    void ajustarTiempoFechaSimulacion();
    void ajustarTiempoFechaFinSimulacion();
    //
    std::time_t mostrarTiempoFechaInicioSimulacion();
    std::time_t mostrarTiempoFechaSimulacion();
    std::time_t mostrarTiempoFechaFinSimulacion();
};

#endif
