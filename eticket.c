#include "eticket.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

void criarDiretorioETickets() {
    #ifdef _WIN32
        system("mkdir e_tickets 2> nul");
    #else
        system("mkdir -p e_tickets");
    #endif
}

int gerarIDUnico() {
    static int counter = 0;
    return (int)(time(NULL) % 100000) + (counter++ % 10000);
}

char* gerarPortao() {
    static char portao[5];
    char letras[] = "ABCDE";
    sprintf(portao, "%c%02d", letras[rand() % 5], 1 + rand() % 30);
    return portao;
}

void gerarETicketMinimalista(Passageiro p, Voo voo, int dia, int mes, int ano) {
    criarDiretorioETickets();
    
    int id = gerarIDUnico();
    char nomeArquivo[100];
    sprintf(nomeArquivo, "e_tickets/%04d_%02d_%02d_%d_%d.txt", 
            ano, mes, dia, voo.codigoRota, id);
    
    FILE *file = fopen(nomeArquivo, "w");
    if(file) {
        fprintf(file, "Data: %02d/%02d/%04d\n", dia, mes, ano);
        fprintf(file, "Horário: %02d:%02d\n", voo.horaVoo, voo.minutoVoo);
        fprintf(file, "Origem: %s\n", voo.origem.cidade);
        fprintf(file, "Destino: %s\n", voo.destino.cidade);
        fprintf(file, "Passageiro: %s\n", p.nome);
        fprintf(file, "Número E-Ticket: %d\n", id);
        fprintf(file, "Código Voo: %d\n", voo.codigoRota);
        fprintf(file, "Portão: %s\n", gerarPortao());
        fclose(file);
    }
}