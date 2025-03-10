#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COR_VERDE "\x1b[32m"   
#define COR_VERMELHO "\x1b[31m" 
#define RESET "\x1b[0m" 
#define FILEIRAS 25
#define COLUNAS 6
#define ID_MAX 100  // Limite de IDs de voo

typedef struct {
    char assento[4];  // Nome do assento (ex: "10A")
    int disponivel;   // 1 = disponível, 0 = ocupado
} Assento;

typedef struct {
    Assento n_assentos[FILEIRAS][COLUNAS]; 
} Matriz;

// Gera o nome do arquivo com base no ID do voo
void obter_nome_arquivo(int id, char *nomeArquivo) {
    snprintf(nomeArquivo, 20, "voo_%d.txt", id);
}

// Carrega os assentos do arquivo do ID ou cria um novo se não existir
void carregar_assentos(Matriz *m, int id) {
    char nomeArquivo[20];
    obter_nome_arquivo(id, nomeArquivo);

    FILE *file = fopen(nomeArquivo, "r");
    if (file) {
        for (int i = 0; i < FILEIRAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                fscanf(file, "%s %d", m->n_assentos[i][j].assento, &m->n_assentos[i][j].disponivel);
            }
        }
        fclose(file);
    } else {
        // Criar um novo voo com todos os assentos disponíveis
        file = fopen(nomeArquivo, "w");
        for (int i = 0; i < FILEIRAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                snprintf(m->n_assentos[i][j].assento, 4, "%d%c", i + 1, 'A' + j);
                m->n_assentos[i][j].disponivel = 1;
                fprintf(file, "%s %d\n", m->n_assentos[i][j].assento, m->n_assentos[i][j].disponivel);
            }
        }
        fclose(file);
    }
}

// Exibe os assentos disponíveis do ID
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

// Reserva um assento em um ID específico
void reservar_assento(Matriz *m, int id) {
    char escolha[4];
    exibir_assentos_disponiveis(m);

    printf("\nEscolha um assento: ");
    scanf("%s", escolha);

    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (strcmp(m->n_assentos[i][j].assento, escolha) == 0) {
                if (m->n_assentos[i][j].disponivel == 1) {
                    m->n_assentos[i][j].disponivel = 0;

                    // Atualizar o arquivo do voo
                    char nomeArquivo[20];
                    obter_nome_arquivo(id, nomeArquivo);
                    FILE *file = fopen(nomeArquivo, "w");
                    if (file) {
                        for (int x = 0; x < FILEIRAS; x++) {
                            for (int y = 0; y < COLUNAS; y++) {
                                fprintf(file, "%s %d\n", m->n_assentos[x][y].assento, m->n_assentos[x][y].disponivel);
                            }
                        }
                        fclose(file);
                    }

                    printf("O assento %s foi reservado com sucesso no voo %d!\n", escolha, id);
                    return;
                } else {
                    printf("O assento %s já está ocupado no voo %d!\n", escolha, id);
                    return;
                }
            }
        }
    }
    printf("Assento inválido!\n");
}

int solicitar_id_voo() {
    int id;
    do {
        printf("Digite o ID do voo (1 a %d): ", ID_MAX);
        scanf("%d", &id);
        if (id < 1 || id > ID_MAX) {
            printf("ID inválido! Escolha um ID entre 1 e %d.\n", ID_MAX);
        }
    } while (id < 1 || id > ID_MAX);
    return id;
}

int main() {
    srand(time(NULL));
    Matriz m;

    int opcao, id;
    do {
        printf("\n==== MENU ===="
               "\n[1] Visualizar Assentos"
               "\n[2] Reservar Assento"
               "\n[0] Sair"
               "\nO que deseja? ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                id = solicitar_id_voo();
                carregar_assentos(&m, id);
                exibir_assentos_disponiveis(&m);
                break;
            case 2:
                id = solicitar_id_voo();
                carregar_assentos(&m, id);
                reservar_assento(&m, id);
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
