#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COR_VERDE "\x1b[32m"   
#define COR_VERMELHO "\x1b[31m" 
#define RESET "\x1b[0m" 
#define FILEIRAS 25
#define COLUNAS 6
#define ARQUIVO_ASSENTOS "assentos.txt"
#define ARQUIVO_VOOS "voos.dat"

typedef struct {
    char assento[4];  // Nome do assento (ex: "10A")
    int disponivel;   // 1 = disponível, 0 = ocupado
} Assento;

typedef struct {
    Assento n_assentos[FILEIRAS][COLUNAS]; 
} Matriz;

typedef struct {
    int id;
    char assento[4];
} Voo;

void carregar_assentos(Matriz *m) {
    FILE *file = fopen(ARQUIVO_ASSENTOS, "r");
    if (file != NULL) {
        for (int i = 0; i < FILEIRAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                fscanf(file, "%s %d", m->n_assentos[i][j].assento, &m->n_assentos[i][j].disponivel);
            }
        }
        fclose(file);
    } else {
        for (int i = 0; i < FILEIRAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                snprintf(m->n_assentos[i][j].assento, 4, "%d%c", i + 1, 'A' + j);
                m->n_assentos[i][j].disponivel = 1;
            }
        }
    }
}

void exibir_assentos_disponiveis(Matriz *m) {
    printf("\n Assentos:\n");
    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (m->n_assentos[i][j].disponivel == 1) {
                printf(COR_VERDE "[%s] " RESET, m->n_assentos[i][j].assento);
            } else {
                printf(COR_VERMELHO "[X] " RESET);
            }
            if (j == 2) printf("   "); // Espaço entre grupos de poltronas para o corredor
        }
        printf("\n");
    }
}

void escolha_de_assento(Matriz *m, int id) {
    char escolha[4];
    exibir_assentos_disponiveis(m);

    printf("\nPor favor, escolha um assento: ");
    scanf("%s", escolha);

    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (strcmp(m->n_assentos[i][j].assento, escolha) == 0) {
                if (m->n_assentos[i][j].disponivel == 1) {
                    m->n_assentos[i][j].disponivel = 0;
                    printf("O assento %s escolhido com sucesso!\n", escolha);
                    return;
                } else {
                    printf("O assento %s já está ocupado!\n", escolha);
                    return;
                }
            }
        }
    }
    printf("Assento invalido!\n");
}

void consultar_voo_e_exibir_assentos(Matriz *m) {
    int id;
    printf("Digite o ID do voo para visualizar os assentos: ");
    scanf("%d", &id);
    exibir_assentos_disponiveis(m);
}

int main() {
    srand(time(NULL));
    Matriz m;
    carregar_assentos(&m);

    int opcao, id;
    do {
        printf("\n==== MENU ===="
               "\n[1] Visualizar Assentos de um Voo"
               "\n[2] Reservar Assento"
               "\n[0] Sair"
               "\n O que deseja? ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                consultar_voo_e_exibir_assentos(&m);
                break;
            case 2:
                printf("Digite o ID do voo: ");
                scanf("%d", &id);
                escolha_de_assento(&m, id);
                break;
            case 0:
                printf("Obrigado! Volte sempre!\n");
                break;
            default:
                printf("Opção inválida!\n");            
                break;
        }
    } while (opcao != 0);
}
