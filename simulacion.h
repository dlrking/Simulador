#ifndef _SIMULACION
#define _SIMULACION

#include "simulador.h"
#include "objetos.h"

class Simulacion {
friend class Simulador;
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
    std::string obtenerStrFechaInicioSimulacion();
    std::string obtenerStrFechaSimulacion();
    std::string obtenerStrFechaFinSimulacion();
    //
    std::string ajustarStrFechaInicioSimulacion();
    std::string ajustarStrFechaSimulacion();
    std::string ajustarStrFechaFinSimulacion();
    //
    std::tm ajustarTmFechaInicioSimulacion();
    std::tm ajustarTmFechaSimulacion();
    std::tm ajustarTmFechaFinSimulacion();
    //
    std::time_t obtenerTiempoFechaInicioSimulacion();
    std::time_t obtenerTiempoFechaSimulacion();
    std::time_t obtenerTiempoFechaFinSimulacion();
    //
    std::time_t ajustarTiempoFechaInicioSimulacion();
    std::time_t ajustarTiempoFechaSimulacion();
    std::time_t ajustarTiempoFechaFinSimulacion();
public:
    // Atributos (públicos)
    std::string strFechaTransferenciaSimulacion;
    std::tm tmFechaTransferenciaSimulacion;
    // Métodos/funciones (públicas) de clase
    std::string mostrarStrFechaInicioSimulacion();
    std::string mostrarStrFechaSimulacion();
    std::string mostrarStrFechaFinSimulacion();
    //
    std::time_t mostrarTiempoFechaInicioSimulacion();
    std::time_t mostrarTiempoFechaSimulacion();
    std::time_t mostrarTiempoFechaFinSimulacion();
    /* Constructor de clase.
     * Usualmente público o protegido.
     * Puede ser privado en ciertos patrones de diseño (singleton).
    */
    Simulacion();
    ~Simulacion();
};

#endif
