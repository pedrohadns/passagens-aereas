#ifndef ROTA_H
#define ROTA_H
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

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
    unsigned int horaVoo, minutoVoo;
    char ehRegular;
    unsigned int diaSemana;
    unsigned int poltronasDisponiveis;
    double distancia;
} Voo;

extern unsigned int quantidadeVoos; // A quantidade de voos pode ser acessada a partir de qualquer fun��o
extern Voo *vetorVoos; // Os vetores que armazenam os dados dos arquivos podem ser acessados a partir de qualquer fun��o

void leString (char *string, int tamanho);
unsigned int obterCodigoVooAnterior (FILE *arquivo);
void cadastrarAeroporto (Aeroporto *aeroporto_sendo_cadastrado, char origemOuDestino);
void criarNomeRota (char *strDestino, Voo rota);
void escreveArquivo (FILE *arquivo, Voo voo);
void imprimeStringnoArquivo (FILE *arquivo, char *string);
void lerHorario (Voo *voo);
void lerDiaSemana (Voo *voo);
void incluirVoo ();
Voo *criarVetorVoos (unsigned int quantidadeVoos);
#endif