#include "simulacion.h"
// Funciones públicas de la clase Simulacion
/*
 */
Simulacion::Simulacion() {
    std::cout << "Constructor Simulacion() ejecutado.\n";
}
/*
 */
Simulacion::~Simulacion() {
    std::cout << "Desstructor ~Simulacion() ejecutado.\n";
}
// Obtenedores (get)
/*
 */
void Simulacion::obtenerStrFechaInicioSimulacion() {
    std::string strEntradaUsuario = "";
    std::cout << "Ingresar fecha de inicio de la simulación \n"
        << "utilizando el siguiente formato: \"YYYY-MM-DD HH:MM\"\n"
        << "P. Ej.: 1950-12-24 19:35 \n";
    std::getline(std::cin, strEntradaUsuario);
    strEntradaUsuario += ":00";
    this->strFechaTransferenciaSimulacion = strEntradaUsuario;
}
/*
 */
void Simulacion::obtenerStrFechaSimulacion() {

}
/*
 */
void Simulacion::obtenerStrFechaFinSimulacion() {
    std::string strEntradaUsuario = "";
    std::cout << "Ingresar fecha de finalización de la simulación \n"
        << "utilizando el siguiente formato: \"YYYY-MM-DD HH:MM\"\n"
        << "P. Ej.: 2550-12-24 19:35 \n";
    std::getline(std::cin, strEntradaUsuario);
    strEntradaUsuario += ":00";
    this->strFechaTransferenciaSimulacion = strEntradaUsuario;
}
// Ajustadores (set)
/*
 */
void Simulacion::ajustarStrTmFechaInicioSimulacion() {
    try {
        std::istringstream streamFechaTransferencia(this->strFechaTransferenciaSimulacion);
        streamFechaTransferencia >> std::get_time(&this->tmFechaTransferenciaSimulacion, "%Y-%m-%d %H:%M:%S");
        if (streamFechaTransferencia.fail()) {
            throw std::invalid_argument("Formato de fecha inválido en Simulacion::ajustarStrFechaInicioSimulacion()");
        } else {
            this->strFechaInicioSimulacion = this->strFechaTransferenciaSimulacion;
            this->tmFechaInicioSimulacion = this->tmFechaTransferenciaSimulacion;
        }
        std::cout << "\nFecha de Inicio de la Simulación: " << "\n"
            << "Año:        " << (this->tmFechaInicioSimulacion.tm_year + 1900) << "\n"
            << "Mes:        " << (this->tmFechaInicioSimulacion.tm_mon + 1)     << "\n"
            << "Día:        " << this->tmFechaInicioSimulacion.tm_mday          << "\n"
            << "Hora:       " << this->tmFechaInicioSimulacion.tm_hour          << "\n"
            << "Minutos:    " << this->tmFechaInicioSimulacion.tm_min           << "\n"
            << "Segundos:   " << this->tmFechaInicioSimulacion.tm_sec           << "\n";
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
/*
 */
void Simulacion::ajustarStrTmFechaSimulacion() {

}
/*
 */
void Simulacion::ajustarStrTmFechaFinSimulacion() {
    std::time_t tiempoFinal = {};
    std::time_t tiempoInicial = {};
    double diferenciaTiempoFinalInicial = 0.0;
    try {
        std::istringstream streamFechaTransferencia(this->strFechaTransferenciaSimulacion);
        streamFechaTransferencia >> std::get_time(&this->tmFechaTransferenciaSimulacion, "%Y-%m-%d %H:%M:%S");
        if (streamFechaTransferencia.fail()) {
            throw std::invalid_argument("Formato de fecha inválido en Simulacion::ajustarStrTmFechaFinSimulacion()");
        } else {
            this->strFechaFinSimulacion = this->strFechaTransferenciaSimulacion;
            tiempoFinal = std::mktime(&this->tmFechaTransferenciaSimulacion);
            tiempoInicial = std::mktime(&this->tmFechaInicioSimulacion);
        }
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    try {
        diferenciaTiempoFinalInicial = std::difftime(tiempoFinal,tiempoInicial);
        if (diferenciaTiempoFinalInicial <= 0) {
            throw std::domain_error("Intervalo de tiempo inválido (negativo o cero) en Simulacion::ajustarStrTmFechaFinSimulacion()");
        } else {
            this->tmFechaFinSimulacion = this->tmFechaTransferenciaSimulacion;
        }
        std::cout << "\nFecha de Finalización de la Simulación: " << "\n"
        << "Año:        " << (this->tmFechaFinSimulacion.tm_year + 1900) << "\n"
        << "Mes:        " << (this->tmFechaFinSimulacion.tm_mon + 1)     << "\n"
        << "Día:        " << this->tmFechaFinSimulacion.tm_mday          << "\n"
        << "Hora:       " << this->tmFechaFinSimulacion.tm_hour          << "\n"
        << "Minutos:    " << this->tmFechaFinSimulacion.tm_min           << "\n"
        << "Segundos:   " << this->tmFechaFinSimulacion.tm_sec           << "\n";
    } catch (const std::domain_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
// Mostradores (show)
/*
 */
std::string Simulacion::mostrarStrFechaInicioSimulacion() {
    return this->strFechaInicioSimulacion;
}
/*
 */
std::string Simulacion::mostrarStrFechaSimulacion() {
    return this->strFechaSimulacion;
}
/*
 */
std::string Simulacion::mostrarStrFechaFinSimulacion() {
    return this->strFechaFinSimulacion;
}
