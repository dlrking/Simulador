#include"relojAplicacion.h"

RelojAplicacion& RelojAplicacion::obtenerInstancia() {
    static RelojAplicacion instancia;
    return instancia;
}

int64_t RelojAplicacion::textoFechaEnMiliseg(const std::string textoFecha) {
    if(textoFecha.empty()) { return 9223372036854775807LL;}

    // Época de referencia: 1 de Enero de 1950
    int año = 1950;
    int mes = 1;
    int dia = 1;
    int hora = 0;
    int minuto = 0;
    int segundo = 0;

    int lectura = std::sscanf(textoFecha.c_str(), "%d/%d/%d,%d:%d:%d",
                              &año, &mes, &dia, &hora, &minuto, &segundo);

    if(lectura !=6 || mes < 1 || mes > 12
        || dia < 1 || dia > diasDelMes(mes, año)
        || hora < 0 || hora > 23
        || minuto < 0 || minuto > 59
        || segundo < 0 || segundo > 59) { return 9223372036854775807LL; }

    int64_t totalDias = 0LL;

    if(año >= 1950) {
        for(int a = 1950; a < año; ++a) {
            totalDias += (esBisiesto(a) ? 366LL : 365LL);
        }
        for(int m = 1; m < mes; ++m) {
            totalDias += static_cast<int64_t>(diasDelMes(m, año));
        }
        totalDias += static_cast<int64_t>(dia - 1);

        int64_t totalMilisegundos = totalDias * 86400000LL;          // 24x60x60x1000 (factor de conversion Dias a ms)
        totalMilisegundos += static_cast<int64_t>(hora) * 3600000LL; // 60x60x1000 (...)
        totalMilisegundos += static_cast<int64_t>(minuto) * 60000LL; // 60x1000 (...)
        totalMilisegundos += static_cast<int64_t>(segundo) * 1000LL; // x1000 (...)

        return totalMilisegundos;
    } else {
        for(int a = 1949; a > año; --a) {
            totalDias += (esBisiesto(a) ? 366LL : 365LL);
        }

        int diasAñoObjetivo = (esBisiesto(año) ? 366LL : 365LL);
        int diasTrascurridosAñoObjetivo = 0;
        for (int m = 1; m < mes; ++m) {
            diasTrascurridosAñoObjetivo += diasDelMes(m, año);
        }
        diasTrascurridosAñoObjetivo += (dia - 1);

        totalDias += static_cast<int64_t>(diasAñoObjetivo - diasTrascurridosAñoObjetivo);

        int64_t totalMilisegundos = -(totalDias * 86400000LL);       // 24x60x60x1000 (...)
        totalMilisegundos += static_cast<int64_t>(hora) * 3600000LL; // 60x60x1000 (...)
        totalMilisegundos += static_cast<int64_t>(minuto) * 60000LL; // 60x1000 (...)
        totalMilisegundos += static_cast<int64_t>(segundo) * 1000LL; // x1000 (...)

        return totalMilisegundos;
    }
}

std::string RelojAplicacion::milisegEnTextoFecha(int64_t milisegundos) {
    FechaHora fh = obtenerFechaHora(milisegundos);
    return fh.texto;
}

FechaHora RelojAplicacion::obtenerFechaHora(int64_t milisegundos) {
    FechaHora fh;

    int64_t numeroDias = milisegundos / 86400000LL;                             // Obtener número de días desde el número de milisegundos
    if(milisegundos < 0 && milisegundos % 86400000LL != 0) { numeroDias--; }    // Obtener el entero inferior para aumentar día con las horas trascurridas desde media noche
    // % Factor de conversión para saber si es la media noche exacta del día
    int residuoDia = static_cast<int>(numeroDias % 7LL);                        // % 7 para saber si 0 Dom, 1 Lun, 2 Mar...
    fh.diaSemana = (residuoDia >= 0) ? residuoDia : (residuoDia + 7);           // Si el residuo es negativo, corregirlo sumando 7 para obtener el correcto

    const std::string dia[7] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
    fh.dia = dia[fh.diaSemana];

    // Descomponer y extraer el número de años
    if(milisegundos >= 0) {
        fh.año = 1950;                                                          // Establecer el año de partida para las cuentas hacia adelante (sentido positivo)
        uint64_t msRestantes = static_cast<uint64_t>(milisegundos);             // Empezamos con msRestantes = milisegundos

        uint64_t msAño = (esBisiesto(fh.año) ? 366ULL : 365ULL) * 86400000ULL;  // Identificar si el año es bisiesto, asignar número de días correspondiente al año y obtener número de ms ese año
        // Reducir el número de msRestantes en un año (expresado en ms)
        while(msRestantes >= msAño) {
            msRestantes -= msAño;                                               // Reducir msRestantes un año
            fh.año++;                                                           // Incrementa el número del año de la estructura FechaHora en uno
            msAño = (esBisiesto(fh.año) ? 366ULL : 365ULL) * 86400000ULL;       // Vuelve a obtener el número de ms del año para el siguiente ciclo
        }

        fh.diaAño = static_cast<int>(msRestantes / 86400000ULL) + 1;            // Dividir entre factor de conversión (Dias a ms) y sumar uno para compensar tiempo extra desde media noche (% Factor de conversion = 0)
        fh.semanaAño = ((fh.diaAño - 1) / 7) + 1;                               // No existe la semana 0, por eso suma + 1. Comentarios anteriores explican porque restar 1 al díaAño

        // Mismo razonamiento de descomponer el tiempo restante en meses
        fh.mes = 1;
        uint64_t msMes = static_cast<uint64_t>(diasDelMes(fh.mes, fh.año)) * 86400000ULL;
        // Restando los días (en ms) del mes, un mes tras otro
        while(msRestantes >= msMes) {
            msRestantes -= msMes;
            fh.mes++;
            msMes = static_cast<uint64_t>(diasDelMes(fh.mes, fh.año)) * 86400000ULL;
        }

        fh.diaMes = static_cast<int>(msRestantes / 86400000ULL) + 1;
        fh.semanaMes = ((fh.diaMes - 1) / 7) + 1;

        msRestantes %= 86400000ULL;
        fh.hora = static_cast<int>(msRestantes / 3600000ULL);
        msRestantes %= 3600000ULL;
        fh.minuto = static_cast<int>(msRestantes / 60000ULL);
        msRestantes %= 60000ULL;
        fh.segundo = static_cast<int>(msRestantes / 1000ULL);
        fh.milisegundo = static_cast<int>(msRestantes % 1000ULL);
    } else {
        fh.año = 1949;
        int64_t msRestantes = milisegundos;

        int64_t msAño = (esBisiesto(fh.año) ? 366LL : 365LL) * 86400000LL;
        while(msRestantes < -msAño) {
            msRestantes += msAño;
            fh.año--;
            msAño = (esBisiesto(fh.año) ? 366LL : 365LL) * 86400000LL;
        }

        msAño += msRestantes;

        fh.diaAño = static_cast<int>(msAño / 86400000LL) + 1;
        fh.semanaAño = ((fh.diaAño - 1) / 7) + 1;

        fh.mes = 1;
        int64_t msMes = static_cast<int64_t>(diasDelMes(fh.mes, fh.año)) * 86400000LL;
        // Restando los días (en ms) del mes, un mes tras otro
        while(msAño >= msMes) {
            msAño -= msMes;
            fh.mes++;
            msMes = static_cast<int64_t>(diasDelMes(fh.mes, fh.año)) * 86400000LL;
        }

        fh.diaMes = static_cast<int>(msAño / 86400000LL) + 1;
        fh.semanaMes = ((fh.diaMes - 1) / 7) + 1;

        msRestantes = msAño;
        msRestantes %= 86400000LL;
        fh.hora = static_cast<int>(msRestantes / 3600000LL);
        msRestantes %= 3600000LL;
        fh.minuto = static_cast<int>(msRestantes / 60000LL);
        msRestantes %= 60000LL;
        fh.segundo = static_cast<int>(msRestantes / 1000LL);
        fh.milisegundo = static_cast<int>(msRestantes % 1000LL);
    }

    char caracteresFecha[24];
    std::snprintf(caracteresFecha, sizeof(caracteresFecha), "%04d/%02d/%02d,%02d:%02d:%02d",
                  fh.año, fh.mes, fh.diaMes, fh.hora, fh.minuto, fh.segundo);
    fh.texto = std::string(caracteresFecha);

    return fh;
}

int RelojAplicacion::diasDelMes(int mes, int año) {
    const int diasPorMes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mes == 2 && esBisiesto(año)) { return 29; }
    return diasPorMes[mes - 1];
}
