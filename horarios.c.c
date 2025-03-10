#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rota.h"

#define MAX_VOOS 100

void escolha_de_assento(int idVoo);
/*indica que existe uma fun��o chamada escolha_de_assento. Permite que chame a fun��o da etapa 3 quando necess�rio.*/

int importarVoos(Voo voos[]) {
    FILE *arquivo = fopen("voos.dat", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de voos!\n");
        return 0;
    }

    int qtd = 0;
    while (qtd < MAX_VOOS && 
           fscanf(arquivo, "%u;%3[^;];%50[^;];%50[^;];%2[^;];%3[^;];%50[^;];%50[^;];%2[^;];%100[^;];%u;%u;%c;%u;%u;%lf",
                  &voos[qtd].codigoRota,
                  voos[qtd].origem.codigoAeroporto,
                  voos[qtd].origem.nomeAeroporto,
                  voos[qtd].origem.cidade,
                  voos[qtd].origem.estado,
                  voos[qtd].destino.codigoAeroporto,
                  voos[qtd].destino.nomeAeroporto,
                  voos[qtd].destino.cidade,
                  voos[qtd].destino.estado,
                  voos[qtd].nomeRota,
                  &voos[qtd].horaVoo,
                  &voos[qtd].minutoVoo,
                  &voos[qtd].ehRegular,
                  &voos[qtd].diaSemana,
                  &voos[qtd].poltronasDisponiveis,
                  &voos[qtd].distancia) == 16) {
        qtd++;
    }
    
    fclose(arquivo);
    return qtd;
}
/*l� os dados de voos do arquivo "voos.dat", armazena as informa��es em um vetor Voo. Os dados de voo s�o lidos e armazenados.
O n�mero de voos lidos � contado pela vari�vel qtd. A cada voo lido, se tiver 16 informa��es certinhas, qtd sobe 1. (As informa��es foram
tiradas do arquivo "rota.c")*/

void salvarVoos(Voo voos[], int qtd) {
    FILE *arquivo = fopen("voos.dat", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar voos!\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(arquivo, "%u;%s;%s;%s;%s;%s;%s;%s;%s;%s;%u;%u;%c;%u;%u;%.2lf\n",
                voos[i].codigoRota,
                voos[i].origem.codigoAeroporto,
                voos[i].origem.nomeAeroporto,
                voos[i].origem.cidade,
                voos[i].origem.estado,
                voos[i].destino.codigoAeroporto,
                voos[i].destino.nomeAeroporto,
                voos[i].destino.cidade,
                voos[i].destino.estado,
                voos[i].nomeRota,
                voos[i].horaVoo,
                voos[i].minutoVoo,
                voos[i].ehRegular,
                voos[i].diaSemana,
                voos[i].poltronasDisponiveis,
                voos[i].distancia);
    }
    fclose(arquivo);
}
/*atualiza o arquivo voos.dat com os dados atuais dos voos. 
Ap�s uma reserva, decrementa o n�mero de poltronas dispon�veis e salva as altera��es no arquivo.*/

void registrarVenda(const Voo *voo)
{
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao registrar venda!\n");
        return;
    }

    fprintf(arquivo, "%u;%s;%s;%02d:%02d;%d\n",
            voo->codigoRota,
            voo->origem.codigoAeroporto,
            voo->destino.codigoAeroporto,
            voo->horaVoo,
            voo->minutoVoo,
            voo->poltronasDisponiveis);

    fclose(arquivo);
}
/*registra uma venda no arquivo vendas.dat. Armazena o c�digo do voo, aeroportos de origem e destino, hor�rio e o n�mero de poltronas 
dispon�veis ap�s a venda.*/

void selecionarHorario(Aeroporto origem, Aeroporto destino)
{
    Voo voos[MAX_VOOS];
    int qtdVoos = importarVoos(voos);
    int indicesValidos[MAX_VOOS];
    int validos = 0;
/*l� o arquivo voos.dat e carrega todos os voos para o array voos*/

    printf("\n=== Voos Dispon�veis ===\n");
    for (int i = 0; i < qtdVoos; i++)
    {
        if (strcmp(voos[i].origem.codigoAeroporto, origem.codigoAeroporto) == 0 &&
            strcmp(voos[i].destino.codigoAeroporto, destino.codigoAeroporto) == 0 &&
            voos[i].poltronasDisponiveis > 0)
        {
/*filtra os voos que correspondem a origem e ao destino desejado pelo usu�rio, al�m de garantir que h� poltronas dispon�veis para a reserva */

            printf("%d - %02d:%02d (%d assentos restantes)\n",
                   validos + 1,
                   voos[i].horaVoo,
                   voos[i].minutoVoo,
                   voos[i].poltronasDisponiveis);
/*Exibe para o usu�rio a lista de voos v�lidos com poltronas dispon�veis, mostrando o hor�rio do voo e o n�mero de assentos restantes */

            indicesValidos[validos] = i;
            validos++;
        }
    }
/*mapeia as posi��es do array voo*/

    if (validos == 0)
    {
        printf("\nNenhum voo dispon�vel para esta rota!\n");
        return;
    }
/*se nenhum voo passar pelo filtro*/

    int escolha;
    printf("\nEscolha o voo (1-%d): ", validos);
    scanf("%d", &escolha);
/*captura a escolha do usu�rio das op��es filtradas*/

    if (escolha < 1 || escolha > validos)
    {
        printf("\nOp��o inv�lida!\n");
        return;
    }
/*verifica se o usuario digitou uma das op��es v�lidas*/

    Voo *vooSelecionado = &voos[indicesValidos[escolha - 1]];
    vooSelecionado->poltronasDisponiveis--;
    salvarVoos(voos, qtdVoos);
    registrarVenda(vooSelecionado);
/*atualiza o n�mero de poltronas dispon�veis. Salva as altera��es no arquivo voos.dat. Registra a venda no arquivo vendas.dat*/

    printf("\nRedirecionando para sele��o de assentos...\n");
    escolha_de_assento(vooSelecionado->codigoRota);

    printf("\nVenda conclu�da com sucesso!\n");
}