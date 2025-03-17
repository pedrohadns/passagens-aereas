#include "dias_do_ano.h"

Feriado feriados[] = {
    {1, 1},   // Confraterniza��o Universal
    {21, 4},  // Tiradentes
    {1, 5},   // Dia do Trabalho
    {7, 9},   // Independ�ncia do Brasil
    {12, 10}, // Nossa Senhora Aparecida
    {2, 11},  // Finados
    {15, 11}, // Proclama��o da Rep�blica
    {25, 12}  // Natal
};

int ehFeriado(int dia, int mes, int ano) {
    for (int i = 0; i < NUM_FERIADOS; i++) {
        if (feriados[i].dia == dia && feriados[i].mes == mes) {
            return 1; // � feriado
        }
    }
    return 0; // N�o � feriado
}

// Fun��o para verificar se uma data cai em um final de semana
int ehFinalDeSemana(int dia, int mes, int ano) {
    struct tm data = {0};
    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;

    mktime(&data);
    
    return (data.tm_wday == 0 || data.tm_wday == 6); // 0 = domingo, 6 = s�bado
}