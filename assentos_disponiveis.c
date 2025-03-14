#include "assentos_disponiveis.h"

unsigned int quantidadeVoos;
Voo *vetorVoos;
int fileiras;

// Gera o nome do arquivo com base no ID do voo
void obter_nome_arquivo(int id, char *nomeArquivo, int dia, int mes, int ano) {
    snprintf(nomeArquivo, 50, "dados-assentos/%02d-%02d-%04d_voo_%d.dat", dia, mes, ano, id);
}

// Carrega os assentos do arquivo do ID ou cria um novo se não existir
void carregar_assentos(Matriz *m, int id, int dia, int mes, int ano) {
    char nomeArquivo[50];
    obter_nome_arquivo(id, nomeArquivo, dia, mes, ano);

    int qntAssentos = vetorVoos[id].poltronasDisponiveis;
    fileiras = qntAssentos / COLUNAS; // Define a quantidade de fileiras de acordo com a quantidade de assentos
    if (qntAssentos % COLUNAS != 0) fileiras++; // Se houver resto, incrementa uma fileira
    
    FILE *file = fopen(nomeArquivo, "r");
    if (file) {
        for (int i = 0; i < fileiras; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                fscanf(file, "%s %d", m->n_assentos[i][j].assento, &m->n_assentos[i][j].disponivel);
            }
        }
        fclose(file);
    } else {
        // Criar um novo voo com todos os assentos disponíveis
        file = fopen(nomeArquivo, "w");
        for (int i = 0; i < fileiras; i++) {
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
    printf("\nAssentos:\n");
    for (int i = 0; i < fileiras; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (m->n_assentos[i][j].disponivel == 1) {
                printf(COR_VERDE "[%3s] " RESET, m->n_assentos[i][j].assento);
            } else {
                printf(COR_VERMELHO "[%3s] " RESET, m->n_assentos[i][j].assento);
            }
            if (j == 2) printf("   "); // Espaço entre grupos de poltronas para o corredor
        }
        printf("\n");
    }
}

// Reserva um assento em um ID específico
void reservar_assento(Matriz *m, int id, int dia, int mes, int ano) {
    char escolha[4];
    exibir_assentos_disponiveis(m);

    printf ("\nEscolha um assento: ");
    fflush (stdin);
    fgets (escolha, 4, stdin);
    escolha[strcspn (escolha, "\n")] = '\0';
    escolha[1] = toupper (escolha[1]);
    escolha[2] = toupper(escolha[2]);

    for (int i = 0; i < fileiras; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (strcmp(m->n_assentos[i][j].assento, escolha) == 0) {
                if (m->n_assentos[i][j].disponivel == 1) {
                    m->n_assentos[i][j].disponivel = 0;

                    // Atualizar o arquivo do voo
                    char nomeArquivo[50];
                    obter_nome_arquivo(id, nomeArquivo, dia, mes, ano);
                    FILE *file = fopen(nomeArquivo, "w");
                    if (file) {
                        for (int x = 0; x < fileiras; x++) {
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
                    reservar_assento (m, id, dia, mes, ano);
                    return;
                }
            }
        }
    }
    printf("Assento inválido! Tente novamente.\n");
    reservar_assento(m, id, dia, mes, ano);
}

int solicitar_id_voo() {
    int id;
    do {
        printf("Digite o ID do voo (0 a %d): ", quantidadeVoos);
        scanf("%d", &id);
        if (id < 0 || id > quantidadeVoos) {
            printf("ID inválido! Escolha um ID entre 0 e %d.\n", quantidadeVoos);
        }
    } while (id < 0 || id > quantidadeVoos);
    return id;
}

int numeroAssentosDisponiveis (Matriz *m){
    int contador = 0;
    for (int i = 0; i < fileiras; i++){
        for (int j = 0; j < COLUNAS; j++){
            contador += m->n_assentos[i][j].disponivel;
        }
    }
    return contador;
}