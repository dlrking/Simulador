#ifndef PALADIN
#define PALADIN

#include "herramientas/relojPaladin.h"
#include "simulacion/estado.h"
#include "simulacion/parametros.h"

class Paladin {
public:
    Paladin(const std::string&, unsigned long long, bool);
    ~Paladin();

    void iniciar();
    void pausar();
    void detener();
    void ajustarVelocidad();

    void actualizar();

    std::string obtenerIdentificador() const { return identificador; }
    bool esInteractivo() const { return interactivo; }
    std::string obtenerTextoEstado() const;
    const FechaHora& obtenerFechaHoraSim() const { return reloj.obtenerFechaHora(); }
    unsigned long long obtenerPaso() const { return reloj.obtenerPaso(); }

private:
    std::string identificador;
    bool interactivo;
    Estado estado;
    float velocidad;
    RelojP reloj;

    void ejecutarCiclo();
    void volcarBitacora();
};

#endif
