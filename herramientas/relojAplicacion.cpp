#include"relojAplicacion.h"

RelojAplicacion& RelojAplicacion::obtenerInstancia() {
    static RelojAplicacion instancia;
    return instancia;
}
