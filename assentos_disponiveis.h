#include "rota.h"
#include <ctype.h>

#define COR_VERDE "\x1b[32m"   
#define COR_VERMELHO "\x1b[31m" 
#define RESET "\x1b[0m" 
#define FILEIRAS 67
#define COLUNAS 6
extern int fileiras;

typedef struct {
    char assento[4];  // Nome do assento (ex: "10A")
    int disponivel;   // 1 = disponível, 0 = ocupado
} Assento;

typedef struct {
    Assento n_assentos[FILEIRAS][COLUNAS]; 
} Matriz;

void obter_nome_arquivo(int id, char *nomeArquivo, int dia, int mes, int ano);
void carregar_assentos(Matriz *m, int id, int dia, int mes, int ano);
void exibir_assentos_disponiveis(Matriz *m);
void reservar_assento(Matriz *m, int id, int dia, int mes, int ano);
int solicitar_id_voo();
int numeroAssentosDisponiveis(Matriz *m);