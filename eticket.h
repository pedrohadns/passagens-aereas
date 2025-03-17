#ifndef ETICKET_H
#define ETICKET_H

#include "pagamento.h"

void gerarEticketCompleto(Passageiro p, Pagamento pagamento_atual, Voo voo, int dia, int mes, int ano);

#endif