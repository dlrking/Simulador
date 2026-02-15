#include "simulacion.h"

int main() {
    setlocale(LC_ALL, "spanish"); // Localización (tildes, acentos, ñ, etcétera)

    std::string txtFechaInicio;
    std::tm tmFechaInicioSimulacion = {}; // Estructura tm () vacía
    std::time_t tiempoFechaInicioSimulacion = {}; // Estructura time_t () vacía

    std::cout << "Ingresar fecha de inicio de la simulación \n"
        << "utilizando el siguiente formato: \"YYYY-MM-DD HH:MM\"\n"
        << "P. Ej. 1950-12-24 19:35 \n";
    std::getline(std::cin, txtFechaInicio);
    txtFechaInicio += ":00";
    std::istringstream ss(txtFechaInicio);

    try{
        ss >> std::get_time(&tmFechaInicioSimulacion, "%Y-%m-%d %H:%M:%S");
        if (ss.fail()) {
            throw std::invalid_argument("Formato de fecha inválido");
        } else {
            tiempoFechaInicioSimulacion = std::mktime(&tmFechaInicioSimulacion);
        }
        std::cout << "\nFecha de Inicio interpretada: " << std::endl;
        std::cout << "Año:      " << (tmFechaInicioSimulacion.tm_year + 1900) << std::endl;
        std::cout << "Mes:      " << (tmFechaInicioSimulacion.tm_mon + 1) << std::endl;
        std::cout << "Día:      " << tmFechaInicioSimulacion.tm_mday << std::endl;
        std::cout << "Hora:     " << tmFechaInicioSimulacion.tm_hour << std::endl;
        std::cout << "Minutos:  " << tmFechaInicioSimulacion.tm_min << std::endl;
        std::cout << "Segundos: " << tmFechaInicioSimulacion.tm_sec << std::endl;
        std::cout << "time_t:   " << tiempoFechaInicioSimulacion << std::endl;
    } catch(const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    Simulacion* pSimulacion = new Simulacion();
    pSimulacion->obtenerStrFechaInicioSimulacion();
    pSimulacion->ajustarStrTmFechaInicioSimulacion();
    std::cout << pSimulacion->mostrarStrFechaInicioSimulacion() << "\n";
    pSimulacion->obtenerStrFechaFinSimulacion();
    pSimulacion->ajustarStrTmFechaFinSimulacion();
    std::cout << pSimulacion->mostrarStrFechaFinSimulacion();
    delete pSimulacion;

    return 0;
}
