#ifndef ETICKET_H
#define ETICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rota.h"
#include "pagamento.h"

int gerarEticketCompleto(const Passageiro *p, const Voo *voo, int dia, int mes, int ano);

#endif
