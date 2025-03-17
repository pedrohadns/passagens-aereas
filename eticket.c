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

// Fun��o para gerar o c�digo do port�o de embarque
void gerar_codigo_portao (const char *nome_voo, int ano, int mes, int dia, char *codigo_portao) {
    unsigned long hash = 5381;
    int c;

    // Calcula o hash do nome do voo (usando a fun��o djb2)
    while ((c = *nome_voo++)){
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Adiciona os componentes da data ao hash
    hash = ((hash << 5) + hash) + (ano % 100); // �ltimos dois d�gitos do ano
    hash = ((hash << 5) + hash) + mes;
    hash = ((hash << 5) + hash) + dia;

    // Gera a letra do port�o (A-Z)
    char letra_portao = 'A' + (hash % 26);

    // Gera o n�mero do port�o (000-099)
    int numero_portao = (hash / 26) % 100;

    // Formata o c�digo do port�o no formato A123
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
        fprintf(file, "Horario: %02d:%02d\n", voo.horaVoo, voo.minutoVoo);
        fprintf(file, "Origem: %s\n", voo.origem.cidade);
        fprintf(file, "Destino: %s\n", voo.destino.cidade);
        fprintf(file, "Passageiro: %s\n", p.nome);
        fprintf(file, "Assento: %s\n", escolha_assento);
        fprintf(file, "Numero E-Ticket: %d\n", id);
        fprintf(file, "Codigo Voo: %d\n", voo.codigoRota);
        gerar_codigo_portao (voo.nomeRota, dia, mes, ano, codigoPortao);
        fprintf(file, "Portao: %s\n", codigoPortao);
        fprintf(file, "Total: R$ %.2lf\n", pagamento_atual.preco);
        fprintf(file, "Forma de Pagamento: %s\n", pagamento_atual.metodoPagamento);
        fclose(file);
        // Mostra para o usu�rio
        printf("Data: %02d/%02d/%04d\n", dia, mes, ano);
        printf("Hor�rio: %02d:%02d\n", voo.horaVoo, voo.minutoVoo);
        printf("Origem: %s\n", voo.origem.cidade);
        printf("Destino: %s\n", voo.destino.cidade);
        printf("Passageiro: %s\n", p.nome);
        printf("Assento: %s\n", escolha_assento);
        printf("N�mero E-Ticket: %d\n", id);
        printf("C�digo Voo: %d\n", voo.codigoRota);
        printf("Port�o: %s\n", codigoPortao);
        printf("Total: R$ %.2lf\n", pagamento_atual.preco);
        printf("Forma de Pagamento: %s\n", pagamento_atual.metodoPagamento);

        printf ("Deseja gerar o pdf? (1-Sim/0-N�o) ");
        int opcaopdf;
        scanf ("%d", &opcaopdf);
        if (opcaopdf){
           executarLaTeX (voo, dia, mes, ano, p, pagamento_atual, codigoPortao, id);
        }
    }
}
