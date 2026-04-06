#ifndef RELOJ_APLICACION
#define RELOJ_APLICACION

#include "encabezados.h"

class RelojAplicacion {
public:
    static RelojAplicacion& obtenerInstancia();

    static std::chrono::system_clock::time_point obtenerInstanteInicialSistema() {return instanteInicialSistema; }

    static std::chrono::system_clock::time_point obtenerTiempoDelSistema() { return std::chrono::system_clock::now(); }
    static std::chrono::steady_clock::time_point obtenerTiempoDelCronometro() { return std::chrono::steady_clock::now(); }

private:
    // Sólo puede haber un objeto de esta clase así que modificamos operadores (prevención de duplicados)
    RelojAplicacion(const RelojAplicacion&) = delete;
    RelojAplicacion& operator=(const RelojAplicacion&) = delete;

    static inline std::chrono::system_clock::time_point instanteInicialSistema;

    RelojAplicacion() { instanteInicialSistema = std::chrono::system_clock::now(); }
    ~RelojAplicacion() = default;
};

#endif
