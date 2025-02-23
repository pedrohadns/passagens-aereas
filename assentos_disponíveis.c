#include <stdio.h>
#include <string.h>
typedef struct {
    char assento[4]; // quantidade de assentos (ex: "10A")
    int disponivel;  // 1 = disponível, 0 = indisponível  
} Assento;
typedef struct {
    Assento n_assentos[10][10]; // usei matriz para informar os locais dos assentos (pode ser que tenha muitos assentos)
} Matriz;
// iniciar a matriz de assentos
void iniciar_matriz(Matriz *m) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            snprintf(m->n_assentos[i][j].assento, 4, "%d%c", i + 1, 'A' + j); // vai colocar o nome do assento (ex: "1A", "1B", etc.)
            m->n_assentos[i][j].disponivel = 1; // vai marcar TODOS os assentos como disponiveis
        }
    }
}
// exibir os assentos disponíveis
void exibir_assentos_disponiveis(Matriz *m) {
    printf("Assentos disponíveis:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (m->n_assentos[i][j].disponivel == 1) {
                printf("[%s] ", m->n_assentos[i][j].assento); // mostra o assento disponível
            } else {
                printf("[X] "); // foi para ficar clean e deixar o assento indisponivel com uma marca (ideia do chat gpt(desculpa))
            }
        }
    }
}
//escolher um assento
void escolha_de_assento(Matriz *m) {
    char escolha[4];
    exibir_assentos_disponiveis(m); // Exibe os assentos disponíveis

    printf("\nEscolha o assento: ");
    scanf("%s", escolha); // escolha é onde ficar o assento que o usuario escolheu (deu certo)

    // procura o assento escolhido dentro da matriz
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(m->n_assentos[i][j].assento, escolha) == 0) { // faz uma comparação entre os assentos (strcmp)
                if (m->n_assentos[i][j].disponivel == 1) {
                    m->n_assentos[i][j].disponivel = 0; // marca o assento como usado
                    printf("Assento %s escolhido!\n", escolha);
                    return; // aqui vai o return para etapa 4
                } else {
                    printf("O assento %s está indisponível. Por favor, escolha outro.\n", escolha);
                    escolha_de_assento(m); // aqui chama outro assento 
                    return escolha_de_assento(m);
                }
            }
        }
    }
    printf("Assento não existe. Tente novamente e tome cuidado com a digitação\n");
    escolha_de_assento(m);
}
int main() {
    Matriz m;
    iniciar_matriz(&m); 
    escolha_de_assento(&m); 
    return 0;
}