#ifndef CRONOMETRO
#define CRONOMETRO

#include "escriba.h"

class Cronometro {
public:
    explicit Cronometro(const char*, const char*, const char*);
    ~Cronometro();

private:
    const char* nombreOrigen;
    const char* nombreFuncion;
    const char* nombreSeccion;
    std::chrono::steady_clock::time_point inicio;
};

#ifndef NDEBUG
    #define CRONOMETRAR(origen, seccion) Cronometro duracion_##__LINE__(origen, __FUNCTION__, seccion)
#else
    #define CRONOMETRAR(origen, seccion)
#endif

#endif
