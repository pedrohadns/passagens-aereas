#ifndef GERARPDF_H
#define GERARPDF_H

#include "eticket.h"
#include <direct.h>  // Para _mkdir
#include <windows.h>  // Para comandos do sistema

void gerar_arquivo_latex(Voo voo, int dia, int mes, int ano, Passageiro passageiro_atual, Pagamento pagamento_atual, char *codigoPortao, int codigoEticket, const char *pasta, const char *nome_arquivo);
void compilar_latex(const char *pasta, const char *nome_arquivo);
void limpar_diretorio(const char *pasta, const char *nome_pdf);
void executarLaTeX (Voo voo, int dia, int mes, int ano, Passageiro passageiro_atual, Pagamento pagamento_atual, char *codigoPortao, int codigoEticket);
#endif