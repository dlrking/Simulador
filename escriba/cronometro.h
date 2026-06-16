#ifndef CRONOMETRO
#define CRONOMETRO

#include "escriba.h"

class Cronometro {
public:
    explicit Cronometro(const std::string&, const std::string&, const std::string&);
    ~Cronometro();

private:
    std::string nombreOrigen;
    std::string nombreFuncion;
    std::string nombreSeccion;
    std::chrono::steady_clock::time_point inicio;
};

#ifndef NDEBUG
    #define CRONOMETRAR(objeto, seccion) Cronometro duracion_##__LINE__(objeto, __FUNCTION__, seccion)
#else
    #define CRONOMETRAR(objeto, seccion)
#endif

#endif
