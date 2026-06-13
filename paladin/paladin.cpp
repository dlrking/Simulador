#include "paladin.h"

// Funciones privadas de clase

/*
 */
void Paladin::inicializarFechaTransferencia() {
    std::cout << "Inicializando en ceros la variable de intercambio (fecha)... \n";
    this->strFechaTransferencia = "";
    this->tmFechaTransferencia = {0};
    this->tiempoFechaTransferencia = 0;
    std::cout << "Variable de intercambio inicializada correctamente. \n";
}

/*
 */
void Paladin::obtenerFecha() {
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
void Paladin::comprobarFormatoFecha() {
    std::cout << "Comprobando formato de la fecha ingresada... \n";
    try {
        std::istringstream streamFechaTransferencia(this->strFechaTransferencia);
        streamFechaTransferencia >> std::get_time(&this->tmFechaTransferencia, "%Y-%m-%d %H:%M:%S");
        if (streamFechaTransferencia.fail()) {
            throw std::invalid_argument("Formato de fecha incorrecto en ::comprobarFormatoFecha() \n");
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
void Paladin::comprobarValidezFecha() {
    std::cout << "Comprobando validez de la fecha ingresada... \n";
    try {
        this->tiempoFechaTransferencia = std::mktime(&this->tmFechaTransferencia);
        // Comprobar que la fecha es mayor a la Época UNIX (1970-01-01 00:00:00)
        if (this->tiempoFechaTransferencia > 0) {
            std::cout << "Fecha posterior a la Época UNIX. \n";
        } else {
            throw std::domain_error("Fecha anterior a la Época UNIX en ::comprobarValidezFecha() \n");
        }
        // Comprobar que el año en la fecha es anterior al año 2036; nos interesa optimizar el uso de memoria
        // Podriamos considerar 2^64 - 2 segundos de simulacion para arquitecturas x64
        if (this->tmFechaTransferencia.tm_year < (2036 - 1900)) {
            std::cout << "Fecha anterior al año 2036 \n";
        } else {
            throw std::domain_error("Fecha final posterior al año 2036 en ::comprobarValidezFecha() \n");
        }
    } catch (const std::domain_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Paladin::ajustarFecha (std::string argumentos) {
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
            throw std::invalid_argument("Argumento incorrecto en ::ajustarFecha() \n");
        }
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Paladin::comprobarIntervaloFecha() {
    try {
        this->numeroSegundos = std::difftime(this->tiempoFinal, this->tiempoInicial);
        this->numeroMinutos = this->numeroSegundos / 60;
        if (this->numeroSegundos > 0) {
            std::cout << "Las fechas final e incial forman un intervalo de tiempo válido (mayor a 0). \n";
            std::cout << "El tiempo a simular es de " << this->numeroSegundos << " segundos. \n";
            std::cout << "El tiempo a simular es de " << this->numeroMinutos << " minutos. \n";
        } else {
            throw std::domain_error("Intervalo de tiempo negativo o cero en ::comprobarIntervaloFecha()");
        }
    } catch (const std::domain_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
 */
void Paladin::inicializarVectorTiempo() {
    std::cout << "Creando e inicializando vector de estructuras de tiempo (tm)... \n";
    this->tmFechaTransferencia = this->tmFechaInicial;
    this->vectorTiempo.push_back(this->tmFechaTransferencia);
    for (int i = 0; i < this->numeroMinutos; i++) {
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
std::string Paladin::mostrarStrFechaInicio() {
    return "\n";
}
/*
 */
std::string Paladin::mostrarStrFecha() {
    return "\n";
}
/*
 */
std::string Paladin::mostrarStrFechaFin() {
    return "\n";
}

/*
 */
Paladin::Paladin() {
    std::cout << "Constructor () ejecutado.\n";
    std::cout << "Inicializando Simulación...\n";
    inicializarFechaTransferencia();
    this->numeroSegundos = 0;
    this->numeroMinutos= 0;
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
    std::cout << "Inicio de la simulación: " << this->mostrarStrFechaInicio();
    std::cout << "Final de la simulación: " << this->mostrarStrFechaFin();
    inicializarVectorTiempo();
}

/*
 */
Paladin::~Paladin() {
    std::cout << "Destructor ~() ejecutado.\n";
}
