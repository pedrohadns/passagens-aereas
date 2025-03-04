#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COR_VERDE "\x1b[32m"   
#define COR_VERMELHO "\x1b[31m" 
#define RESET "\x1b[0m" 

#define LINHAS 10
#define COLUNAS 10
#define ARQUIVO_ASSENTOS "assentos.dat"

typedef struct {
    char assento[4];  // Nome do assento (ex: "10A")
    int disponivel;   // 1 = disponível, 0 = ocupado
} Assento;

typedef struct {
    Assento n_assentos[LINHAS][COLUNAS]; 
} Matriz;

// salvar os assentos no arquivo
void salvar_assentos(Matriz *m) {
    FILE *file = fopen(ARQUIVO_ASSENTOS, "wb");
    if (file == NULL) {
        printf("Erro ao salvar os assentos.\n");
        return;
    }
    fwrite(m, sizeof(Matriz), 1, file);
    fclose(file);
}

// carregar os assentos do arquivo
void carregar_assentos(Matriz *m) {
    FILE *file = fopen(ARQUIVO_ASSENTOS, "rb");
    if (file != NULL) {
        fread(m, sizeof(Matriz), 1, file);
        fclose(file);
    } else {
        // Se o arquivo não existir, inicializa a matriz com assentos disponíveis
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                snprintf(m->n_assentos[i][j].assento, 4, "%d%c", i + 1, 'A' + j);
                m->n_assentos[i][j].disponivel = 1;
            }
        }
        salvar_assentos(m);  
    }
}

void exibir_assentos_disponiveis(Matriz *m) {
    printf("\n Visualização dos Assentos:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (m->n_assentos[i][j].disponivel == 1) {
                printf(COR_VERDE "[%s] " RESET, m->n_assentos[i][j].assento);
            } else {
                printf(COR_VERMELHO "[X] " RESET);
            }
        }
        printf("\n");
    }
}

void escolha_de_assento(Matriz *m) {
    char escolha[4];
    exibir_assentos_disponiveis(m); 

    printf("\nEscolha um assento: ");
    scanf("%s", escolha);

    // Procurar o assento na matriz
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (strcmp(m->n_assentos[i][j].assento, escolha) == 0) {
                if (m->n_assentos[i][j].disponivel == 1) {
                    m->n_assentos[i][j].disponivel = 0;
                    printf("assento %s escolhido com sucesso! tenha uma boa viagem\n", escolha);
                    salvar_assentos(m);  // Atualiza o arquivo com a nova reserva
                    return;
                } else {
                    printf("infelizmente o assento %s já está ocupado! Por favor, escolha outro.\n", escolha);
                    escolha_de_assento(m); 
                    return;
                }
            }
        }
    }
    printf("escorregou ai? Código de assento inválido!\n");
    escolha_de_assento(m);
}


int main() {
    Matriz m;
    carregar_assentos(&m); 

    int opcao;
    do {
        printf("\n==== SELEÇÃO DE ASSENTOS ====\n");
        printf("[1] Mostrar assentos\n");
        printf("[2] Reservar assento\n");
        printf("[0] Sair\n");
        printf("o'que deseja? ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibir_assentos_disponiveis(&m);
                break;
            case 2:
                escolha_de_assento(&m);
                break;
            case 0:
                printf("ação encerrada\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
