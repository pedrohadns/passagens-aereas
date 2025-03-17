#include "dias_do_ano.h"
#include "assentos_disponiveis.h"

#ifndef PAGAMENTO_H
#define PAGAMENTO_H

// Estrutura para armazenar os dados do passageiro
typedef struct {
    char nome[100];
    char rg[20];
    char cpf[20];
    char dataNascimento[9];
    char telefone[20];
    char email[100];
    int bagagemExtra;
} Passageiro;

// Estrutura para armazenar os dados do pagamento
typedef struct {
    double preco;
    char metodoPagamento[20];
} Pagamento;

// Estrutura para armazenar o funcionário
typedef struct {
    char nome[50];
    char cargo[10]; // "gerente" ou "vendedor"
    char matricula[12]; // 11 dígitos + terminador de string
} Funcionario;

// Declaração das funções
int validarFuncionario(char *matricula, char *nome, char *cargo);
int calcularDiasAteVoo(int dia_voo, int mes_voo, int ano_voo);
double obterFatorDia (int dia, int mes, int ano);
double calcularFatorPER(int dias_ate_voo);
double calcularFatorRET(int dias_retorno);
double calcularFatorPROC(double ocupacao_percentual);
double calcularPrecoVoo(Voo voo, int dia_voo, int mes_voo, int ano_voo, int dias_retorno);
void realizarPagamento(Passageiro passageiro, Pagamento *pagamento, Voo voo, int dia_voo, int mes_voo, int ano_voo);
void registrarPagamentoArquivo(Pagamento pagamento, Passageiro passageiro, Voo voo, int dia, int mes, int ano);
void cadastrarPassageiro(Passageiro *passageiro);
#endif // PAGAMENTO_H