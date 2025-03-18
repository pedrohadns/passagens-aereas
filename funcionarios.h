#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H
#include "rota.h"
#include <ctype.h>

typedef struct {
    int id;
    char nome[50];
    char matricula[12]; // 11 dígitos + terminador de string
    char cargo[10]; // "gerente" ou "vendedor"
} Funcionario;

extern Funcionario *funcionarios_cadastrados;
extern int quantidadeFuncionarios;

void escreveArquivoFuncionarios (FILE *arquivo, Funcionario funcionario_sendo_escrito);
void capitalizarString (char *str);
void incluirFuncionario ();
Funcionario *criarVetorFuncionarios (int quantidadeFuncionarios);
void alterarFuncionario ();
void escreveVetorInteiroFuncionarios ();

#endif