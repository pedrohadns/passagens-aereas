#ifndef PAGAMENTO_H
#define PAGAMENTO_H

// Estrutura para armazenar os dados do passageiro
typedef struct {
    char nome[100];
    char rg[20];
    char cpf[20];
    char telefone[20];
    char email[100];
    int bagagemExtra;
} Passageiro;

// Estrutura para armazenar os dados do pagamento
typedef struct {
    double preco;
    char metodoPagamento[20];
} Pagamento;

// Declaração das funções
void realizarPagamento(Pagamento *pagamento, double precoTotal);
void cadastrarPassageiro(Passageiro *passageiro);
void registrarPagamentoArquivo(Pagamento *pagamento, Passageiro *passageiro);

#endif // PAGAMENTO_H
