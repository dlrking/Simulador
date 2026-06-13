#ifndef RELOJ_APLICACION
#define RELOJ_APLICACION

#include "encabezados.h"

class RelojAplicacion {
public:
    static RelojAplicacion& obtenerInstancia();
    static std::chrono::system_clock::time_point obtenerInstanteInicial() { return tiempoInicial; }
    static std::chrono::system_clock::time_point obtenerInstanteActual() { return std::chrono::system_clock::now(); }
    static std::chrono::steady_clock::time_point obtenerCronometro() { return std::chrono::steady_clock::now(); }

private:
    // Sólo puede haber un objeto de esta clase así que modificamos operadores (=) (prevención de duplicados)
    RelojAplicacion(const RelojAplicacion&) = delete;
    RelojAplicacion& operator=(const RelojAplicacion&) = delete;

    static inline std::chrono::system_clock::time_point tiempoInicial;

    RelojAplicacion() { tiempoInicial = std::chrono::system_clock::now(); }
    ~RelojAplicacion() = default;
};

#endif
