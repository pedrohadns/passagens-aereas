#include "main.h"

typedef struct{
    char codigoAeroporto[4];
    char nomeAeroporto[50];
    char cidade[50];
    char estado[3];
} Aeroporto;

typedef struct{
    unsigned int codigoRota;
    Aeroporto origem;
    Aeroporto destino;
    char nomeRota[100];
    unsigned char horaVoo, minutoVoo;
    bool ehRegular;
    unsigned char diaSemana;
    unsigned char poltronasDisponiveis;
    double distancia;
} Voo;

Voo *voos;
unsigned int qtdVoos;