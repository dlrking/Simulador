#include "relojPaladin.h"

RelojP::RelojP(int64_t tiempoSistema, int resolucionMinutos = 1)
: paso(0), tiempoSistema(tiempoSistema), resolucion(resolucionMinutos) {
    std::string mensaje = "Reloj del Paladín instanciado e inicializado correctamente,";
    actualizarFechaHora();
    mensaje += "Fecha y Hora Virtual actualizada," + fechaHora.texto;
    ES_DEP(idEscriba, mensaje);
}

void RelojP::avanzarPaso() {
    CRONOMETRAR(idEscriba, "RelojP::avanzarPaso()");
    std::string mensaje = "Paso (simulación): " + std::to_string(paso);
    ES_DEP(idEscriba, mensaje);
    paso++;
    mensaje = "Siguiente: " + std::to_string(paso);
    ES_DEP(idEscriba, mensaje);
    mensaje = "Fecha y Hora (virtual): " + fechaHora.texto;
    ES_DEP(idEscriba, mensaje);
    actualizarFechaHora();
    mensaje = "Siguiente: " + fechaHora.texto;
    ES_DEP(idEscriba, mensaje);
    mensaje = "La Simulación ha dado un paso correctamente";
    ES_DEP(idEscriba, mensaje);

}

void RelojP::ajustarResolucion(int nuevaResolucion) {
    std::string mensaje = "Resolución (simulación): " + std::to_string(resolucion);
    ES_DEP(idEscriba, mensaje);
    resolucion = nuevaResolucion;
    mensaje = "Resolución (usuario): " + std::to_string(nuevaResolucion);
    ES_DEP(idEscriba, mensaje);
    mensaje = "Resolución (simulación): " + std::to_string(resolucion);
    ES_DEP(idEscriba, mensaje);
}

void RelojP::actualizarFechaHora() {
    int64_t miliSegPorPaso = static_cast<int64_t>(resolucion) * 60LL * 1000LL; // LL por unsigned long long/int64_t
    int64_t totalMiliSeg = tiempoSistema + (paso * miliSegPorPaso);

    const int64_t limiteMax = 9223372036854775807LL;
    if (totalMiliSeg > limiteMax) { totalMiliSeg = limiteMax; }

    int64_t miliSegRestantes = totalMiliSeg;

    // Referencia (arbitraria): Domingo 1 de Enero de 1950 (0)

    int64_t totalDiasDesdeReferencia = totalMiliSeg / 86400000LL;
    fechaHora.diaSemana = static_cast<int>(totalDiasDesdeReferencia % 7LL);
    if (fechaHora.diaSemana < 0) { fechaHora.diaSemana += 7; }

    // Ajustar valores en la fecha y hora de la simulación
    /*fechaHora.año = ptm->tm_year + 1900;
    fechaHora.mes = ptm->tm_mon + 1;
    fechaHora.diaMes = ptm->tm_mday;
    fechaHora.diaSemana = ptm->tm_wday;
    fechaHora.hora = ptm->tm_hour;
    fechaHora.minuto = ptm->tm_min;
    fechaHora.segundo = ptm->tm_sec;
    */

    // Convertir fecha a texto con formato
    std::stringstream ss;
    //ss << std::put_time(ptm, "%Y/%m/%d,%H:%M:%S");
    //fechaHora.texto = ss.str();
}

