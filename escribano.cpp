#include "escribano.h"

Escribano& Escribano::obtenerInstancia() {
    static Escribano instancia;
    return instancia;
}

void Escribano::escribirBorrador(const std::string& origen, nivelDeRegistro nivel, const std::string& funcion, std::string mensaje) {
    std::chrono::system_clock::time_point puntoTiempo = Simulador::obtenerTiempoSistema();
    if (nivel < nivelMinimoDeRegistro) { return; }
    if (borrador[origen].size() >= tamañoTamponDeRegistros) { transcribirBorrador(origen);}
    std::stringstream suceso;
    suceso << obtenerTextoFecha() << ","
           << obtenerTextoNivelesDeRegistro(nivel) << ","
           << "[" << origen  << "],"
           << "[" << funcion << "],"
           << mensaje;
    borrador[origen].push_back(suceso.str());
}

void Escribano::transcribirBorrador(const std::string& origen) {
    if (borrador[origen].empty()) { return; }
    std::ofstream& capitulo = obtenerBitacora(origen);
    if (capitulo.is_open()) {
        for (const auto& iterador : borrador[origen]) {
            capitulo << iterador << "\n";
        }
        capitulo.flush();
    }
    borrador[origen].clear();
}

void Escribano::transcribirTodosLosBorradores() {
    for (const auto& [origen, _] : borrador) { transcribirBorrador(origen); }
}

void Escribano::cerrarCapitulo(const std::string& origen) {
    transcribirBorrador(origen);
    std::ofstream& capitulo = obtenerBitacora(origen);
    if (capitulo.is_open()) { capitulo.close(); }
    capitulo.clear();
}

void Escribano::cerrarBitacora() {
    transcribirTodosLosBorradores();
    for (const auto& [origen, capitulo] : bitacora) { cerrarCapitulo(origen); }
    bitacora.clear();
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
    std::chrono::system_clock::time_point puntoTiempo = Simulador::obtenerTiempoSistema();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(puntoTiempo);
    std::stringstream flujoTexto;
    flujoTexto << std::put_time(std::localtime(&tiempo), "%Y%m%d%H%M%S");
    return flujoTexto.str();
}

std::ofstream& Escribano::obtenerBitacora(const std::string& origen) {
    auto iterador = bitacora.find(origen);
    // Si el flujo para el origen no existe, crearlo
    if (iterador == bitacora.end()) {
        // Si la carpeta no existe, crearla
        if (!std::filesystem::exists(nombreBitacora)) {
            std::filesystem::create_directories(nombreBitacora);
        }
        // Asignar nombre al archivo (en principio los logs se separan por el objeto que los crea)
        std::string capitulo = nombreBitacora + "/" + origen + ".csv";
        bitacora[origen] = std::make_unique<std::ofstream>(capitulo, std::ios::app);
        return *bitacora[origen];
    }
    return *(iterador->second);
}

std::string Escribano::obtenerTextoNivelesDeRegistro(nivelDeRegistro nivel) {
    switch(nivel) {
        case nivelDeRegistro::DEPURACION  : return "[DEPURACIÓN]    ";
        case nivelDeRegistro::INFORMACION : return "[INFORMACIÓN]   ";
        case nivelDeRegistro::ADVERTENCIA : return "[ADVERTENCIA]   ";
        case nivelDeRegistro::ERROR       : return "[ERROR]         ";
        default                           : return "[INDEFINIDO]    ";
    }
}

std::string Escribano::obtenerTextoFecha() {
    std::chrono::system_clock::time_point puntoTiempo = Simulador::obtenerTiempoSistema();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(puntoTiempo);
    std::stringstream flujoTexto;
    flujoTexto << "[" << std::put_time(std::localtime(&tiempo), "%Y-%m-%d %H:%M:%S") << "]";
    return flujoTexto.str();
}

