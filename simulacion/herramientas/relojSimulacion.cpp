#include "relojSimulacion.h"

RelojSimulacion::RelojSimulacion(long inicioUnix, int resolucionSegundos)
: tickActual(0), anclaUnix(inicioUnix), resolucion(resolucionSegundos) {
    actualizarFechaVirtual();
}

void RelojSimulacion::avanzarTick() {
    tickActual++;
    actualizarFechaVirtual();
}

void RelojSimulacion::actualizarFechaVirtual() {
    // Total virtual time since epoch
    std::time_t tiempoVirtual = static_cast<std::time_t>(anclaUnix + (tickActual * resolucion));

    // Decompose into TM structure (Thread-safe on local stack for single-threaded tick)
    std::tm* ptm = std::localtime(&tiempoVirtual);

    // Populate the POD fields
    fechaActual.año = ptm->tm_year + 1900;
    fechaActual.mes = ptm->tm_mon + 1;
    fechaActual.diaMes = ptm->tm_mday;
    fechaActual.diaSemana = ptm->tm_wday;
    fechaActual.hora = ptm->tm_hour;
    fechaActual.minuto = ptm->tm_min;
    fechaActual.segundo = ptm->tm_sec;

    // Pre-format the string for the Escribano to avoid redundant formatting
    std::stringstream ss;
    ss << std::put_time(ptm, "%Y-%m-%d %H:%M:%S");
    fechaActual.texto = ss.str();
}

