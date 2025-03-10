#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rota.h"

#define MAX_VOOS 100

void escolha_de_assento(int idVoo);
/*indica que existe uma função chamada escolha_de_assento. Permite que chame a função da etapa 3 quando necessário.*/

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
/*lê os dados de voos do arquivo "voos.dat", armazena as informações em um vetor Voo. Os dados de voo são lidos e armazenados.
O número de voos lidos é contado pela variável qtd. A cada voo lido, se tiver 16 informações certinhas, qtd sobe 1. (As informações foram
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
Após uma reserva, decrementa o número de poltronas disponíveis e salva as alterações no arquivo.*/

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
/*registra uma venda no arquivo vendas.dat. Armazena o código do voo, aeroportos de origem e destino, horário e o número de poltronas 
disponíveis após a venda.*/

void selecionarHorario(Aeroporto origem, Aeroporto destino)
{
    Voo voos[MAX_VOOS];
    int qtdVoos = importarVoos(voos);
    int indicesValidos[MAX_VOOS];
    int validos = 0;
/*lê o arquivo voos.dat e carrega todos os voos para o array voos*/

    printf("\n=== Voos Disponíveis ===\n");
    for (int i = 0; i < qtdVoos; i++)
    {
        if (strcmp(voos[i].origem.codigoAeroporto, origem.codigoAeroporto) == 0 &&
            strcmp(voos[i].destino.codigoAeroporto, destino.codigoAeroporto) == 0 &&
            voos[i].poltronasDisponiveis > 0)
        {
/*filtra os voos que correspondem a origem e ao destino desejado pelo usuário, além de garantir que há poltronas disponíveis para a reserva */

            printf("%d - %02d:%02d (%d assentos restantes)\n",
                   validos + 1,
                   voos[i].horaVoo,
                   voos[i].minutoVoo,
                   voos[i].poltronasDisponiveis);
/*Exibe para o usuário a lista de voos válidos com poltronas disponíveis, mostrando o horário do voo e o número de assentos restantes */

            indicesValidos[validos] = i;
            validos++;
        }
    }
/*mapeia as posições do array voo*/

    if (validos == 0)
    {
        printf("\nNenhum voo disponível para esta rota!\n");
        return;
    }
/*se nenhum voo passar pelo filtro*/

    int escolha;
    printf("\nEscolha o voo (1-%d): ", validos);
    scanf("%d", &escolha);
/*captura a escolha do usuário das opções filtradas*/

    if (escolha < 1 || escolha > validos)
    {
        printf("\nOpção inválida!\n");
        return;
    }
/*verifica se o usuario digitou uma das opções válidas*/

    Voo *vooSelecionado = &voos[indicesValidos[escolha - 1]];
    vooSelecionado->poltronasDisponiveis--;
    salvarVoos(voos, qtdVoos);
    registrarVenda(vooSelecionado);
/*atualiza o número de poltronas disponíveis. Salva as alterações no arquivo voos.dat. Registra a venda no arquivo vendas.dat*/

    printf("\nRedirecionando para seleção de assentos...\n");
    escolha_de_assento(vooSelecionado->codigoRota);

    printf("\nVenda concluída com sucesso!\n");
}