#include "escriba.h"

Escriba& Escriba::obtenerInstancia() {
    static Escriba instancia;
    return instancia;
}

// La variable origen idealmente es una de SISTEMA, SIMULADOR, CRONOMETRO, ENTIDAD, etc...
void Escriba::escribirBorrador(const std::string& origen, nivelDeRegistro nivel, const std::string& funcion, std::string mensaje) {
    // Si el nivel de registro de este récord no es suficiente, salir
    if (nivel < nivelRegistro) { return; }
    // Obtener marca de tiempo
    std::chrono::system_clock::time_point tiempoReloj = RelojAplicacion::obtenerInstanteActual();
    // Del vector borrador, obtener la etiqueta de origen (un vector de texto)
    std::vector<std::string>& registro = borrador[origen];
    // Volcar el registro si su tamaño es mayor al "buffer"
    if (registro.size() >= numeroDeRegistros) { transcribirBorrador(origen);}
    // Escribir el suceso: Fecha y Hora, [Nivel de Registro], [Objeto de origen del mensaje], [Función que genera el mensaje], Mensaje
    // El mensaje puede contener, a su vez, varias columnas extras de diferentes tipos separados por coma
    std::stringstream suceso;
    suceso << obtenerTextoFecha(tiempoReloj) << ","
           << obtenerTextoNivelDeRegistro(nivel) << ","
           << "[" << origen  << "],"
           << "[" << funcion << "],"
           << mensaje;
    // Agregar suceso al registro
    registro.push_back(suceso.str());
}

void Escriba::mostrarBorrador() {
    // Obtener iterador del mapa (borrador) e iterar sobre el mapa
    std::map<std::string, std::vector<std::string>>::iterator iterador;
    for (iterador = borrador.begin(); iterador != borrador.end(); ++iterador) {
        std::cout << "Origen: [" << iterador->first << "]" << std::endl;
        const std::vector<std::string>& mensajes = iterador->second;
        // Si el vector de mensajes está vacío, salir
        if (mensajes.size() == 0) { return; }
        // Iterar sobre el vector de mensajes e imprimirlos
        for (size_t i = 0; i < mensajes.size(); ++i) {
            std::cout << "  > " << mensajes[i] << std::endl;
        }
    }
}

void Escriba::transcribirBorrador(const std::string& origen) {
    // Si no hay cosa alguna en el borrador, salir
    if (borrador[origen].empty()) { return; }
    // Obtener flujo de archivo de la bitácora en la etiqueta de origen (un apuntador a un flujo de archivo de std::ofstream)
    std::ofstream& capitulo = obtenerBitacora(origen);
    if (capitulo.is_open()) {
        // Obtener registro del borrador
        const std::vector<std::string>& registro = borrador[origen];
        // Iterar sobre cada elemento del registro y agregarlo a la bitácora
        for (size_t it = 0; it < registro.size(); ++it) {
            capitulo << registro[it] << "\n";
        }
        // Guardar capítulo en disco
        capitulo.flush();
    }
    // Limpiar borrador
    borrador[origen].clear();
}

void Escriba::transcribirBorradores() {
    // Obtener iterador del borrador
    std::map<std::string, std::vector<std::string>>::iterator it;
    // Iterar sobre todos los borradores y transcribirlos cada uno
    for (it = borrador.begin(); it != borrador.end(); ++it) { transcribirBorrador(it->first); }
}

void Escriba::cerrarCapitulo(const std::string& origen) {
    transcribirBorrador(origen);
    // Obtener flujo de archivo de la bitácora en la etiqueta de origen (un apuntador a un flujo de archivo de std::ofstream)
    std::ofstream& capitulo = obtenerBitacora(origen);
    // Cerrar flujo si está abierto
    if (capitulo.is_open()) { capitulo.close(); }
    // Limpiar bitácora en la etiqueta de origen (ahora es un apuntador vacío)
    capitulo.clear();
}

void Escriba::cerrarBitacora() {
    transcribirBorradores();
    // Obtener iterador del mapa (bitácora) e iterar sobre el mapa cerrando cada flujo para cada etiqueta de origen y limpiar
    std::map<std::string, std::unique_ptr<std::ofstream>>::iterator it;
    for (it = bitacora.begin(); it != bitacora.end(); ++it) { cerrarCapitulo(it->first); }
    bitacora.clear();
    borrador.clear();
}

void Escriba::ajustarNivelMinimoDeRegistro(const std::string& nuevoNivel) {
    if (nuevoNivel == "Depuración") { nivelRegistro = nivelDeRegistro::DEPURACION; }
    else if (nuevoNivel == "Información") { nivelRegistro = nivelDeRegistro::INFORMACION; }
    else if (nuevoNivel == "Advertencia") { nivelRegistro = nivelDeRegistro::ADVERTENCIA; }
    else if (nuevoNivel == "Error") { nivelRegistro = nivelDeRegistro::ERROR; }
    else { throw std::invalid_argument("Argumento incorrecto en ajustarNivelMinimoDeRegistro()"); }
}

std::string Escriba::obtenerNivelMinimoDeRegistro() {
    switch(nivelRegistro) {
        case nivelDeRegistro::DEPURACION  : return "Depuración";
        case nivelDeRegistro::INFORMACION : return "Información";
        case nivelDeRegistro::ADVERTENCIA : return "Advertencia";
        case nivelDeRegistro::ERROR       : return "Error";
        default                           : return "Indefinido";
    }
}

std::string Escriba::obtenerNombreBitacora() {
    // El patrón de guardado de los logs de la aplicación es "carpeta de logs" / "Objeto origen.csv" (para mensajes del Tecnico o del Sistema) o también puede ser "carpeta de logs" / "Fecha de ejecucion"
    // O también puede ser "carpeta de logs" / "AñoMesDia (de ejecución)"  / "Objeto origen.csv"
    std::chrono::system_clock::time_point puntoTiempo = RelojAplicacion::obtenerInstanteActual();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(puntoTiempo);
    std::stringstream flujoTexto;
    flujoTexto << std::put_time(std::localtime(&tiempo), "%Y%m%d%H");
    return flujoTexto.str();
}

std::ofstream& Escriba::obtenerBitacora(const std::string& origen) {
    try {
        std::map<std::string, std::unique_ptr<std::ofstream>>::iterator it = bitacora.find(origen); // Iterador del mapa
        // Si no existe apuntador al flujo en la etiqueta de origen, crearla
        // De lo contrario, devolver el apuntador al flujo que encuentre
        if (it == bitacora.end()) {
            std::filesystem::path capitulo = std::filesystem::absolute(directorio);
            // Si el origen es Sistema o Tecnico, guardar logs en logs/origen.csv
            // de lo contrario, guardar en logs/aaaammdd/origen.csv
            if (origen == "SISTEMA" || origen == "TECNICO") {
                // Si la carpeta no existe, crearla
                if (!std::filesystem::exists(capitulo)) {
                    std::filesystem::create_directories(capitulo);
                }
                // Asignar nombre al archivo (en principio los logs se separan por el objeto que los crea)
                capitulo = capitulo / (origen + ".csv");
            } else {
                capitulo = capitulo / std::filesystem::absolute(nombreBitacora);
                if (!std::filesystem::exists(capitulo)) {
                    std::filesystem::create_directories(capitulo);
                }
                capitulo = capitulo / (origen + ".csv");
            }
            // La bitácora en la etiqueta de origen es un apuntador a un flujo de std::ostream
            bitacora[origen] = std::make_unique<std::ofstream>(capitulo, std::ios::out | std::ios::app);
            // Si el flujo está cerrado, arrojar error, de lo contrario devolver el apuntador al flujo
            if (!bitacora[origen]->is_open()) {
                std::string mensaje = obtenerTextoFecha(RelojAplicacion::obtenerInstanteActual()) + ","
                + "[CRÍTICO],[ESCRIBANO],Escriba::obtenerBitacora(),"
                + "No se pudo obtener bitácora,"
                + "Error: No se pudo abrir archivo" + std::string(capitulo) + "\n";
                std::cerr << mensaje;
            }
            // Devolver apuntador creado
            return *bitacora[origen];
        }
        // Devolver apuntador encontrado
        return *(it->second);
    } catch(const std::exception& error) {
        // En caso de no poder obtener la bitácora, crear e imprimir mensaje de error
        std::string mensaje = obtenerTextoFecha(RelojAplicacion::obtenerInstanteActual()) + ","
            + "[CRÍTICO],[ESCRIBANO],Escriba::obtenerBitacora(),"
            + "No se pudo obtener bitácora " + origen + ","
            + "Error: " + error.what() + "\n";
        std::cerr << mensaje;
        throw;
    }
}

std::string Escriba::obtenerTextoNivelDeRegistro(nivelDeRegistro nivel) {
    switch(nivel) {
        case nivelDeRegistro::DEPURACION  : return "[DEPURACIÓN]";
        case nivelDeRegistro::INFORMACION : return "[INFORMACIÓN]";
        case nivelDeRegistro::ADVERTENCIA : return "[ADVERTENCIA]";
        case nivelDeRegistro::ERROR       : return "[ERROR]";
        default                           : return "[INDEFINIDO]";
    }
}

std::string Escriba::obtenerTextoFecha(std::chrono::system_clock::time_point argsTiempo) {
    std::time_t tiempo = std::chrono::system_clock::to_time_t(argsTiempo);
    std::stringstream flujoTexto;
    // El formato de fecha para las entradas del escriba es AAAA/MM/DD,HH:M:S
    flujoTexto << std::put_time(std::localtime(&tiempo), "%Y/%m/%d,%H:%M:%S");
    return flujoTexto.str();
}

