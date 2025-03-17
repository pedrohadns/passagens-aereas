#ifndef DIAS_DO_ANO_H
#define DIAS_DO_ANO_H

#include <stdio.h>
#include <time.h>
#include <string.h>

// Estrutura para armazenar os feriados
typedef struct {
    int dia;
    int mes;
} Feriado;

// Tamanho do vetor de feriados
#define NUM_FERIADOS 8

int ehFeriado(int dia, int mes, int ano);
int ehFinalDeSemana(int dia, int mes, int ano);
#endif // DIAS_DO_ANO_H