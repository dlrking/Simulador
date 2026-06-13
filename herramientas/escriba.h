#ifndef ESCRIBANO
#define ESCRIBANO

#include "relojAplicacion.h"

enum class nivelDeRegistro {
    DEPURACION,
    INFORMACION,
    ADVERTENCIA,
    ERROR
};

class Escriba {
public:
    // Función que siempre retorna una referencia a una variable estática de esta misma clase, sin modificarla
    static Escriba& obtenerInstancia();

    // Escriba crea un vector borrador en memoria con las entradas de diversos logs y con etiquetas para poder filtrar el registro
    void escribirBorrador(const std::string&, nivelDeRegistro, const std::string&, std::string);
    void mostrarBorrador();
    // Transcribir guarda el vector borrador en disco
    void transcribirBorrador(const std::string&);
    void transcribirTodosLosBorradores();
    // No es un nombre muy evidente: Cerrar capítulo permite cerrar el ofstream de un borrador en la bitacora
    void cerrarCapitulo(const std::string&);
    void cerrarBitacora();

    // Funciones publicas para modificar o exponer algunos atributos de Escriba
    void ajustarTamañoTamponDeRegistros(size_t nuevoTampon) { numeroDeRegistros = nuevoTampon; }
    void ajustarNivelMinimoDeRegistro(const std::string&);
    void ajustarDirectorioBitacora(const std::string& nuevoDirectorio) {  directorioBase = nuevoDirectorio; }
    size_t obtenerTamañoTamponDeRegistros() { return numeroDeRegistros; }
    std::string obtenerNivelMinimoDeRegistro();
    std::string obtenerDirectorioBase() { return directorioBase; }


private:
    // Sólo puede haber un objeto de esta clase así que modificamos operadores (=) (prevención de duplicados)
    Escriba(const Escriba&) = delete;
    Escriba& operator=(const Escriba&) = delete;

    // (Configuración) El número máximo de registros en memoria antes de transcribirBorrador/escribir en disco
    size_t numeroDeRegistros = 300;
    // (Configuración) Nivel mínimo de registro
    nivelDeRegistro nivelMinimoDeRegistro = nivelDeRegistro::DEPURACION;

    // Directorio predeterminado para los logs
    std::string directorioBase = "logs";
    // Nombre para la subcarpeta con los logs de la simulación en curso
    std::string nombreBitacora; // "~/.../logs/xyz"

    // Mapas del tipo (Etiqueta de origen, vector<Mensajes>) y (Etiqueta de origen, apuntador_inteligente_unico<Flujo de salida>)
    // Idealmente, la etiqueta de origen es el nombre de la clase que invoca al escriba
    std::map<std::string, std::vector<std::string>> borrador;
    // La bitácora, a continuación
    std::map<std::string, std::unique_ptr<std::ofstream>> bitacora;

    std::string obtenerNombreBitacora();
    std::ofstream& obtenerBitacora(const std::string&);
    std::string obtenerTextoNivelDeRegistro(nivelDeRegistro);
    std::string obtenerTextoFecha(const std::chrono::system_clock::time_point);

    Escriba() { nombreBitacora = obtenerNombreBitacora(); }
    ~Escriba() { cerrarBitacora(); }
};

#ifndef NDEBUG
    #define ES_DEP(origen, mensaje) Escriba::obtenerInstancia().escribirBorrador(origen, nivelDeRegistro::DEPURACION, __FUNCTION__, mensaje)
    #define ES_ASE(condicion, origen, mensaje)\
    if (!(condicion)) {\
        Escriba::obtenerInstancia().escribirBorrador(origen, nivelDeRegistro::ADVERTENCIA, __FUNCTION__, "[ASERCIÓN ERRÓNEA]," + std::string(mensaje));\
        Escriba::obtenerInstancia().cerrarBitacora();\
        assert(condicion);\
    }
#else
    #define ES_DEP(origen, mensaje)
    #define ES_ASE(condicion, origen, mensaje)
#endif

#define ES_INF(origen, mensaje) Escriba::obtenerInstancia().escribirBorrador(origen, nivelDeRegistro::INFORMACION, __FUNCTION__, mensaje)
#define ES_ADV(origen, mensaje) Escriba::obtenerInstancia().escribirBorrador(origen, nivelDeRegistro::ADVERTENCIA, __FUNCTION__, mensaje)
#define ES_ERR(origen, mensaje) Escriba::obtenerInstancia().escribirBorrador(origen, nivelDeRegistro::ERROR, __FUNCTION__, mensaje)

#endif
