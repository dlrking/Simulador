#ifndef CRONOMETRO
#define CRONOMETRO

#include "escribano.h"

class Cronometro {
public:
    explicit Cronometro(const std::string&, const std::string&, const std::string&);
    ~Cronometro();

private:
    std::string nombreObjeto;
    std::string nombreFuncion;
    std::string nombreSeccion;
    std::chrono::steady_clock::time_point inicio;
};

#ifndef NDEBUG
    #define CRONOMETRAR(objeto, seccion) Cronometro duracion_##__LINE__(objeto, __FUNCTION__, seccion)
#else
    #define CRONOMETRAR(origen, seccion)
#endif

#endif
