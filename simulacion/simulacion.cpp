#include "simulacion.h"

// Funciones privadas de clase

/*
 */
void Simulacion::inicializarFechaTransferencia() {
    std::cout << "Inicializando en ceros la variable de intercambio (fecha)... \n";
    this->strFechaTransferencia = "";
    this->tmFechaTransferencia = {0};
    this->tiempoFechaTransferencia = 0;
    std::cout << "Variable de intercambio inicializada correctamente. \n";
}

/*
 */
void Simulacion::obtenerFecha() {
    std::string strEntradaUsuario = "";
    std::cout << "Por favor ingresar la fecha solicitada \n"
    << "utilizando el siguiente formato: \"YYYY-MM-DD HH:MM\" \n"
    << "(P. Ej.: 1971-01-01 00:00) \n";
    std::getline(std::cin, strEntradaUsuario);
    strEntradaUsuario += ":00";
    this->strFechaTransferencia = strEntradaUsuario;
}

/*
 */
void Simulacion::comprobarFormatoFecha() {
    std::cout << "Comprobando formato de la fecha ingresada... \n";
    try {
        std::istringstream streamFechaTransferencia(this->strFechaTransferencia);
        streamFechaTransferencia >> std::get_time(&this->tmFechaTransferencia, "%Y-%m-%d %H:%M:%S");
        if (streamFechaTransferencia.fail()) {
            throw std::invalid_argument("Formato de fecha incorrecto en Simulacion::comprobarFormatoFecha() \n");
        } else {
            std::cout << "El formato de la fecha ingresada es correcto. \n";
            std::cout << "La fecha ingresada e interpretada es la siguiente: \n"
            << "Año:        " << (this->tmFechaTransferencia.tm_year + 1900) << "\n"
            << "Mes:        " << (this->tmFechaTransferencia.tm_mon + 1)     << "\n"
            << "Día:        " << this->tmFechaTransferencia.tm_mday          << "\n"
            << "Hora:       " << this->tmFechaTransferencia.tm_hour          << "\n"
            << "Minutos:    " << this->tmFechaTransferencia.tm_min           << "\n"
            << "Segundos:   " << this->tmFechaTransferencia.tm_sec           << "\n";
        }
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 * Estas comprobaciones nos permiten garantizar que el número de minutos y segundos
 * no excede las limitaciones de memoria de 32-bits o dicho de otra manera,
 * que el número de minutos y segundos a simular siempre es finito, entero, pequeño
 * y no desborda la memoria. Las diferencias de tiempo deberían poderse calcular
 * en una variable entera sin necesidad de hacer conversión segura de flotante a entero
 */
void Simulacion::comprobarValidezFecha() {
    std::cout << "Comprobando validez de la fecha ingresada... \n";
    try {
        this->tiempoFechaTransferencia = std::mktime(&this->tmFechaTransferencia);
        // Comprobar que la fecha es mayor a la Época UNIX (1970-01-01 00:00:00)
        if (this->tiempoFechaTransferencia > 0) {
            std::cout << "Fecha posterior a la Época UNIX. \n";
        } else {
            throw std::domain_error("Fecha anterior a la Época UNIX en Simulacion::comprobarValidezFecha() \n");
        }
        // Comprobar que el año en la fecha es anterior al año 3000
        if (this->tmFechaTransferencia.tm_year < (3000 - 1900)) {
            std::cout << "Fecha anterior al año 3000 \n";
        } else {
            throw std::domain_error("Fecha anterior a la Época UNIX en Simulacion::comprobarValidezFecha() \n");
        }
    } catch (const std::domain_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Simulacion::ajustarFecha (std::string argumentos) {
    std::cout << "Función ajustar fecha ejecutada con parámetros: " << argumentos << " \n";
    try {
        if (argumentos == "Inicial") {
            try {
                std::cout << "Ajustando fecha inicial de la simulación... \n";
                this->tmFechaInicial = this->tmFechaTransferencia;
                this->tiempoInicial = this->tiempoFechaTransferencia;
                std::cout << "Fecha de inicio ajustada correctamente. \n";
                inicializarFechaTransferencia();
            } catch (const std::bad_cast& error) {
                std::cerr << "Error de asignación en Simulación::ajustarFecha. \n" << error.what() << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else if (argumentos == "Final") {
            try {
                std::cout << "Ajustando fecha final de la simulación... \n";
                this->tmFechaFinal = this->tmFechaTransferencia;
                this->tiempoFinal = this->tiempoFechaTransferencia;
                std::cout << "Fecha de finalización ajustada correctamente. \n";
                inicializarFechaTransferencia();
            } catch (const std::bad_cast& error) {
                std::cerr << "Error de asignación en Simulación::ajustarFecha. \n" << error.what() << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else {
            throw std::invalid_argument("Argumento incorrecto en Simulacion::ajustarFecha() \n");
        }
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Simulacion::comprobarIntervaloFecha() {
    try {
        this->tiempoSimulacionSegundos = std::difftime(this->tiempoFinal, this->tiempoInicial);
        this->tiempoSimulacionMinutos = this->tiempoSimulacionSegundos / 60;
        if (this->tiempoSimulacionSegundos > 0) {
            std::cout << "Las fechas final e incial forman un intervalo de tiempo válido (mayor a 0). \n";
            std::cout << "El tiempo a simular es de " << this->tiempoSimulacionSegundos << " segundos. \n";
            std::cout << "El tiempo a simular es de " << this->tiempoSimulacionMinutos << " minutos. \n";
        } else {
            throw std::domain_error("Intervalo de tiempo negativo o cero en Simulacion::comprobarIntervaloFecha()");
        }
    } catch (const std::domain_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Simulacion::inicializarVectorTiempo() {
    std::cout << "Creando e inicializando vector de estructuras de tiempo (tm)... \n";
    this->tmFechaTransferencia = this->tmFechaInicial;
    this->vectorTiempo.push_back(this->tmFechaTransferencia);
    for (int i = 0; i < this->tiempoSimulacionMinutos; i++) {
        this->tmFechaTransferencia.tm_min += 1;
        std::mktime(&this->tmFechaTransferencia);
        this->vectorTiempo.push_back(this->tmFechaTransferencia);
    }
    for (int i = 0; i < this->vectorTiempo.size(); i++) {
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &this->vectorTiempo[i]);
        std::cout << buffer << std::endl;
    }
    std::cout << "Vector creado e inicializado correctamente. \n";
}

// Funciones públicas de clase

/*
 */
std::string Simulacion::mostrarStrFechaInicioSimulacion() {
    return "\n";
}
/*
 */
std::string Simulacion::mostrarStrFechaSimulacion() {
    return "\n";
}
/*
 */
std::string Simulacion::mostrarStrFechaFinSimulacion() {
    return "\n";
}

/*
 */
Simulacion::Simulacion() {
    std::cout << "Constructor Simulacion() ejecutado.\n";
    std::cout << "Inicializando Simulación...\n";
    inicializarFechaTransferencia();
    this->tiempoSimulacionSegundos = 0;
    this->tiempoSimulacionMinutos= 0;
    std::cout << "Introducir fecha y hora inicial de la simulación: \n";
    obtenerFecha();
    comprobarFormatoFecha();
    comprobarValidezFecha();
    ajustarFecha("Inicial");
    std::cout << "Introducir fecha y hora final de la simulación: \n";
    obtenerFecha();
    comprobarFormatoFecha();
    comprobarValidezFecha();
    ajustarFecha("Final");
    comprobarIntervaloFecha();
    std::cout << "Inicio de la simulación: " << this->mostrarStrFechaInicioSimulacion();
    std::cout << "Final de la simulación: " << this->mostrarStrFechaFinSimulacion();
    inicializarVectorTiempo();
}

/*
 */
Simulacion::~Simulacion() {
    std::cout << "Destructor ~Simulacion() ejecutado.\n";
}
