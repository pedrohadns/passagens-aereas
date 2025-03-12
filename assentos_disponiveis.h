#include "rota.h"
#include <time.h>

#define COR_VERDE "\x1b[32m"   
#define COR_VERMELHO "\x1b[31m" 
#define RESET "\x1b[0m" 
#define FILEIRAS 50
#define COLUNAS 6
#define ID_MAX 100  // Limite de IDs de voo
extern int fileiras;

typedef struct {
    char assento[4];  // Nome do assento (ex: "10A")
    int disponivel;   // 1 = disponível, 0 = ocupado
} Assento;

typedef struct {
    Assento n_assentos[FILEIRAS][COLUNAS]; 
} Matriz;