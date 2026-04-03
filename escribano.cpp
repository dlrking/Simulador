#include "escribano.h"

Escribano& Escribano::obtenerInstancia() {
    static Escribano instancia;
    return instancia;
}

// La variable origen idealmente es una de SISTEMA, SIMULADOR, CRONOMETRO, ENTIDAD, etc...
void Escribano::escribirBorrador(const std::string& origen, nivelDeRegistro nivel, const std::string& funcion, std::string mensaje) {
    std::chrono::system_clock::time_point puntoTiempo = RelojAplicacion::obtenerTiempoDelSistema();
    if (nivel < nivelMinimoDeRegistro) { return; }
    std::vector<std::string>& registroActual = borrador[origen];
    if (registroActual.size() >= tamañoTamponDeRegistros) { transcribirBorrador(origen);}
    std::stringstream suceso;
    suceso << obtenerTextoFecha() << ","
           << obtenerTextoNivelesDeRegistro(nivel) << ","
           << "[" << origen  << "],"
           << "[" << funcion << "],"
           << mensaje;
    registroActual.push_back(suceso.str());
}

void Escribano::mostrarBorrador() {
    std::map<std::string, std::vector<std::string>>::iterator iterador;
    for (iterador = borrador.begin(); iterador != borrador.end(); ++iterador) {
        std::cout << "Origen: [" << iterador->first << "]" << std::endl;
        const std::vector<std::string>& mensajes = iterador->second;
        for (size_t i = 0; i < mensajes.size(); ++i) {
            std::cout << "  > " << mensajes[i] << std::endl;
        }
    }
}


void Escribano::transcribirBorrador(const std::string& origen) {
    if (borrador[origen].empty()) { return; }
    std::ofstream& capitulo = obtenerBitacora(origen);
    if (capitulo.is_open()) {
        const std::vector<std::string>& anotacion = borrador[origen];
        for (size_t it = 0; it < anotacion.size(); ++it) {
            capitulo << anotacion[it] << "\n";
        }
        capitulo.flush();
    }
    borrador[origen].clear();
}

void Escribano::transcribirTodosLosBorradores() {
    std::map<std::string, std::vector<std::string>>::iterator it;
    for (it = borrador.begin(); it != borrador.end(); ++it) { transcribirBorrador(it->first); }
}

void Escribano::cerrarCapitulo(const std::string& origen) {
    transcribirBorrador(origen);
    std::ofstream& capitulo = obtenerBitacora(origen);
    if (capitulo.is_open()) { capitulo.close(); }
    capitulo.clear();
}

void Escribano::cerrarBitacora() {
    transcribirTodosLosBorradores();
    std::map<std::string, std::unique_ptr<std::ofstream>>::iterator it;
    for (it = bitacora.begin(); it != bitacora.end(); ++it) { cerrarCapitulo(it->first); }
    bitacora.clear();
    borrador.clear();
}

void Escribano::ajustarNivelMinimoDeRegistro(const std::string& nuevoNivel) {
    if (nuevoNivel == "Depuración") { nivelMinimoDeRegistro = nivelDeRegistro::DEPURACION; }
    else if (nuevoNivel == "Información") { nivelMinimoDeRegistro = nivelDeRegistro::INFORMACION; }
    else if (nuevoNivel == "Advertencia") { nivelMinimoDeRegistro = nivelDeRegistro::ADVERTENCIA; }
    else if (nuevoNivel == "Error") { nivelMinimoDeRegistro = nivelDeRegistro::ERROR; }
    else { throw std::invalid_argument("Argumento incorrecto en ajustarNivelMinimoDeRegistro()"); }
}

std::string Escribano::obtenerNivelMinimoDeRegistro() {
    switch(nivelMinimoDeRegistro) {
        case nivelDeRegistro::DEPURACION  : return "Depuración";
        case nivelDeRegistro::INFORMACION : return "Información";
        case nivelDeRegistro::ADVERTENCIA : return "Advertencia";
        case nivelDeRegistro::ERROR       : return "Error";
        default                           : return "Indefinido";
    }
}

std::string Escribano::obtenerNombreBitacora() {
    std::chrono::system_clock::time_point puntoTiempo = RelojAplicacion::obtenerTiempoDelSistema();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(puntoTiempo);
    std::stringstream flujoTexto;
    flujoTexto << std::put_time(std::localtime(&tiempo), "%Y%m%d%H%M%S");
    return flujoTexto.str();
}

std::ofstream& Escribano::obtenerBitacora(const std::string& origen) {
    try {
        std::map<std::string, std::unique_ptr<std::ofstream>>::iterator it = bitacora.find(origen);
        // Si el flujo para el origen no existe, crearlo
        if (it == bitacora.end()) {
            std::filesystem::path capitulo;
            std::filesystem::path directorio = std::filesystem::absolute(directorioBase);
            // Variar carpeta destino segun el origen del récord
            if (origen == "SISTEMA" || origen == "SIMULADOR") {
                // Si la carpeta no existe, crearla
                if (!std::filesystem::exists(directorio)) {
                    std::filesystem::create_directories(directorio);
                }
                // Asignar nombre al archivo (en principio los logs se separan por el objeto que los crea)
                capitulo = directorio / (origen + ".csv");
            } else {
                directorio = directorio / std::filesystem::absolute(nombreBitacora);
                if (!std::filesystem::exists(directorio)) {
                    std::filesystem::create_directories(directorio);
                }
                capitulo = directorio / (origen + ".csv");
            }
            bitacora[origen] = std::make_unique<std::ofstream>(capitulo, std::ios::out | std::ios::app);
            if (!bitacora[origen]->is_open()) {
                std::string mensaje = obtenerTextoFecha() + ","
                + "[CRÍTICO],[ESCRIBANO],Escribano::obtenerBitacora(),"
                + "No se pudo obtener bitácora,"
                + "Error: No se pudo abrir archivo" + std::string(capitulo) + "\n";
                std::cerr << mensaje;
            }
            return *bitacora[origen];
        }
        return *(it->second);
    } catch(const std::exception& error) {
        std::string mensaje = obtenerTextoFecha() + ","
            + "[CRÍTICO],[ESCRIBANO],Escribano::obtenerBitacora(),"
            + "No se pudo obtener bitácora " + origen + ","
            + "Error: " + error.what() + "\n";
        std::cerr << mensaje;
        throw;
    }
}

std::string Escribano::obtenerTextoNivelesDeRegistro(nivelDeRegistro nivel) {
    switch(nivel) {
        case nivelDeRegistro::DEPURACION  : return "[DEPURACIÓN]";
        case nivelDeRegistro::INFORMACION : return "[INFORMACIÓN]";
        case nivelDeRegistro::ADVERTENCIA : return "[ADVERTENCIA]";
        case nivelDeRegistro::ERROR       : return "[ERROR]";
        default                           : return "[INDEFINIDO]";
    }
}

std::string Escribano::obtenerTextoFecha() {
    std::chrono::system_clock::time_point puntoTiempo = RelojAplicacion::obtenerTiempoDelSistema();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(puntoTiempo);
    std::stringstream flujoTexto;
    flujoTexto << "[" << std::put_time(std::localtime(&tiempo), "%Y-%m-%d %H:%M:%S") << "]";
    return flujoTexto.str();
}

