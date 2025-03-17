#include "gerarpdf.h"
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

// Função para gerar o código do portão de embarque
void gerar_codigo_portao (const char *nome_voo, int ano, int mes, int dia, char *codigo_portao) {
    unsigned long hash = 5381;
    int c;

    // Calcula o hash do nome do voo (usando a função djb2)
    while ((c = *nome_voo++)){
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Adiciona os componentes da data ao hash
    hash = ((hash << 5) + hash) + (ano % 100); // Últimos dois dígitos do ano
    hash = ((hash << 5) + hash) + mes;
    hash = ((hash << 5) + hash) + dia;

    // Gera a letra do portão (A-Z)
    char letra_portao = 'A' + (hash % 26);

    // Gera o número do portão (000-099)
    int numero_portao = (hash / 26) % 100;

    // Formata o código do portão no formato A123
    sprintf(codigo_portao, "%c%03d", letra_portao, numero_portao);
}

void gerarEticketCompleto(Passageiro p, Pagamento pagamento_atual, Voo voo, int dia, int mes, int ano) {
    criarDiretorioETickets();
    
    int id = gerarIDUnico();
    char nomeArquivo[100], codigoPortao[5];
    sprintf(nomeArquivo, "e_tickets/%04d_%02d_%02d_%d_%d.txt", 
            ano, mes, dia, voo.codigoRota, id);
    
    FILE *file = fopen(nomeArquivo, "w");
    if(file) {
        // Escreve no arquivo
        fprintf(file, "Data: %02d/%02d/%04d\n", dia, mes, ano);
        fprintf(file, "Horário: %02d:%02d\n", voo.horaVoo, voo.minutoVoo);
        fprintf(file, "Origem: %s\n", voo.origem.cidade);
        fprintf(file, "Destino: %s\n", voo.destino.cidade);
        fprintf(file, "Passageiro: %s\n", p.nome);
        fprintf(file, "Número E-Ticket: %d\n", id);
        fprintf(file, "Código Voo: %d\n", voo.codigoRota);
        gerar_codigo_portao (voo.nomeRota, dia, mes, ano, codigoPortao);
        fprintf(file, "Portão: %s\n", codigoPortao);
        fclose(file);
        // Mostra para o usuário
        printf("Data: %02d/%02d/%04d\n", dia, mes, ano);
        printf("Horário: %02d:%02d\n", voo.horaVoo, voo.minutoVoo);
        printf("Origem: %s\n", voo.origem.cidade);
        printf("Destino: %s\n", voo.destino.cidade);
        printf("Passageiro: %s\n", p.nome);
        printf("Número E-Ticket: %d\n", id);
        printf("Código Voo: %d\n", voo.codigoRota);
        printf("Portão: %s\n", codigoPortao);

        printf ("Deseja gerar o pdf? (1-Sim/0-Não) ");
        int opcaopdf;
        scanf ("%d", &opcaopdf);
        if (opcaopdf){
           executarLaTeX (voo, dia, mes, ano, p, pagamento_atual, codigoPortao, id);
        }
    }
}
