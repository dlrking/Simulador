#include "relojPaladin.h"

RelojP::RelojP(unsigned long long tiempoSistema, int resolucionMinutos = 1)
: paso(0), tiempoSistema(tiempoSistema), resolucion(resolucionMinutos) {
    actualizarFechaHora();
}

void RelojP::avanzarPaso() {
    paso++;
    actualizarFechaHora();
}

void RelojP::actualizarFechaHora() {
    // Tiempo recorrido desde el tiempoSistema según el número de pasos y la resolución
    std::time_t tiempoVirtual = static_cast<std::time_t>(tiempoSistema + (paso * resolucion * 60));

    // Descomponer tiempoVirtual en una estructura tm
    std::tm* ptm = std::localtime(&tiempoVirtual);

    // Ajustar valores en la fecha y hora de la simulación
    fechaHora.año = ptm->tm_year + 1900;
    fechaHora.mes = ptm->tm_mon + 1;
    fechaHora.diaMes = ptm->tm_mday;
    fechaHora.diaSemana = ptm->tm_wday;
    fechaHora.hora = ptm->tm_hour;
    fechaHora.minuto = ptm->tm_min;
    fechaHora.segundo = ptm->tm_sec;

    // Convertir fecha a texto con formato
    std::stringstream ss;
    ss << std::put_time(ptm, "%Y/%m/%d,%H:%M:%S");
    fechaHora.texto = ss.str();
}

int RelojP::obtenerDiasDelMes(int mes, int año) const {
    const int numeroDeDiasPorMes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mes == 2 && esBisiesto(año)) { return 29; }
    return numeroDeDiasPorMes[mes - 1];
}

