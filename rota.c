#include "rota.h"

void leString (char *string, int tamanho){
    fflush (stdin);
    fgets (string, tamanho + 1, stdin);
    string[strcspn (string, "\n")] = '\0';
}

unsigned int obterCodigoVooAnterior (FILE *arquivo){
    if (arquivo == NULL) return 0;
    char buffer[256]; // Armazena a �ltima linha
    while (fgets (buffer, 256, arquivo)){ // L� cada linha do arquivo e para na �ltima quando fgets retorna NULL
        buffer[strspn (buffer, "\n")] = 0;
    }
    unsigned int codigoRotaAnterior = 0;
    sscanf (buffer, "%u", &codigoRotaAnterior);
    return codigoRotaAnterior + 1;
}

void cadastrarAeroporto (Aeroporto *aeroporto_sendo_cadastrado, char origemOuDestino){
    char opcao[8];
    if (origemOuDestino == 'o'){
        strcpy (opcao, "origem");
    }
    else if (origemOuDestino == 'd'){
        strcpy (opcao, "destino");
    }
    printf ("Digite o c�digo do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->codigoAeroporto, 3);
    printf ("Digite o nome do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->nomeAeroporto, 50);
    printf ("Digite a cidade do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->cidade, 50);
    printf ("Digite a UF do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->estado, 2);
}

void criarNomeRota (char *strDestino, Voo rota){
    strcpy (strDestino, rota.origem.nomeAeroporto);
    strcat (strDestino, "[");
    strcat (strDestino, rota.origem.codigoAeroporto);
    strcat (strDestino, "] - ");
    strcat (strDestino, rota.destino.nomeAeroporto);
    strcat (strDestino, "[");
    strcat (strDestino, rota.destino.codigoAeroporto);
    strcat (strDestino, "]");
}

void imprimeStringnoArquivo (FILE *arquivo, char *string){
    fputs (string, arquivo);
    fputs (";", arquivo);
}

void escreveArquivo (FILE *arquivo, Voo voo){
    fseek (arquivo, 0, SEEK_END);
    char str_numero_convertido[50]; // Vari�vel para armazenar o n�mero convertido para string
    sprintf (str_numero_convertido, "%d;", voo.codigoRota);
    fputs (str_numero_convertido, arquivo);
    imprimeStringnoArquivo (arquivo, voo.origem.codigoAeroporto);
    imprimeStringnoArquivo (arquivo, voo.origem.nomeAeroporto);
    imprimeStringnoArquivo (arquivo, voo.origem.cidade);
    imprimeStringnoArquivo (arquivo, voo.origem.estado);
    imprimeStringnoArquivo (arquivo, voo.destino.codigoAeroporto);
    imprimeStringnoArquivo (arquivo, voo.destino.nomeAeroporto);
    imprimeStringnoArquivo (arquivo, voo.destino.cidade);
    imprimeStringnoArquivo (arquivo, voo.destino.estado);
    imprimeStringnoArquivo (arquivo, voo.nomeRota);
    sprintf (str_numero_convertido, "%d;", voo.horaVoo);
    fputs (str_numero_convertido, arquivo);
    sprintf (str_numero_convertido, "%d;", voo.minutoVoo);
    fputs (str_numero_convertido, arquivo);
    sprintf (str_numero_convertido, "%c;", voo.ehRegular);
    fputs (str_numero_convertido, arquivo);
    sprintf (str_numero_convertido, "%d;", voo.diaSemana);
    fputs (str_numero_convertido, arquivo);
    sprintf (str_numero_convertido, "%d;", voo.poltronasDisponiveis);
    fputs (str_numero_convertido, arquivo);
    sprintf (str_numero_convertido, "%lf\n", voo.distancia);
    fputs (str_numero_convertido, arquivo);
}

void lerDiaSemana (Voo *voo){
    do{
        getchar ();
        printf ("Digite o dia da semana do voo (1-7): ");
        scanf (" %d", &voo->diaSemana);
        if (voo->diaSemana < 1 || voo->diaSemana > 7){
            printf ("Dia da semana inv�lido. Tente novamente.\n");
        }
    } while (voo->diaSemana < 1 || voo->diaSemana > 7);
}

void lerHorario (Voo *voo){
    do{
        getchar ();
        printf ("Digite o hor�rio do voo (hh mm), no formato 24 horas: ");
        scanf (" %d", &voo->horaVoo);
        scanf (" %d", &voo->minutoVoo);
        if (voo->horaVoo < 0 || voo->horaVoo > 23 || voo->minutoVoo < 0 || voo->minutoVoo > 59){
            printf ("Hor�rio inv�lido. Tente novamente.\n");
        }
    } while (voo->horaVoo < 0 || voo->horaVoo > 23 || voo->minutoVoo < 0 || voo->minutoVoo > 59);
}

void incluirVoo (){
    FILE *arquivo = fopen ("voos.dat", "a+");
    if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo\n");
        incluirVoo ();
    }
    Voo novoVoo; // Declara uma vari�vel do tipo 'voo' para armazenar os dados do vo� a ser cadastrado
    novoVoo.codigoRota = obterCodigoVooAnterior (arquivo);
    cadastrarAeroporto (&novoVoo.origem, 'o');
    cadastrarAeroporto (&novoVoo.destino, 'd');
    criarNomeRota (novoVoo.nomeRota, novoVoo);
    lerHorario (&novoVoo);
    printf ("O voo � regular? Voos regulares acontecem todos os dias (s/n): ");
    scanf (" %c", &novoVoo.ehRegular);
    if (novoVoo.ehRegular == 'n' || novoVoo.ehRegular == 'N'){
        lerDiaSemana (&novoVoo);
    }
    else {
        novoVoo.ehRegular = 'S';
        novoVoo.diaSemana = 0;
    }
    printf ("Digite a quantidade de poltronas dispon�veis: ");
    scanf (" %d", &novoVoo.poltronasDisponiveis);
    if (novoVoo.poltronasDisponiveis < 0){novoVoo.poltronasDisponiveis *= -1;}
    printf ("Digite a dist�ncia do voo (em milhas): ");
    scanf (" %lf", &novoVoo.distancia);
    if (novoVoo.distancia < 0){novoVoo.distancia *= -1;}
    fseek (arquivo, 0, SEEK_END);
    escreveArquivo (arquivo, novoVoo);
    fclose (arquivo);
}

Voo *criarVetorVoos (unsigned int quantidadeVoos){
    FILE *arquivoVoos = fopen ("voos.dat", "r");
    if (arquivoVoos == NULL){
        printf ("Erro ao abrir o arquivo de voos.\n");
        return NULL;
    }
    Voo *vetorVoos;
    vetorVoos = (Voo *) malloc (quantidadeVoos * sizeof (Voo));
    if (vetorVoos == NULL){
        printf ("Erro ao alocar mem�ria.\n");
        return NULL;
    }

    for (unsigned int i = 0; i < quantidadeVoos; i++){
        fscanf (arquivoVoos, "%u;%4[^;];%50[^;];%50[^;];%3[^;];%4[^;];%50[^;];%50[^;];%3[^;];%100[^;];%u;%u;%c;%u;%u;%lf\n",
            &vetorVoos[i].codigoRota, 
            vetorVoos[i].origem.codigoAeroporto, 
            vetorVoos[i].origem.nomeAeroporto, 
            vetorVoos[i].origem.cidade, 
            vetorVoos[i].origem.estado, 
            vetorVoos[i].destino.codigoAeroporto, 
            vetorVoos[i].destino.nomeAeroporto, 
            vetorVoos[i].destino.cidade, 
            vetorVoos[i].destino.estado, 
            vetorVoos[i].nomeRota, 
            &vetorVoos[i].horaVoo, 
            &vetorVoos[i].minutoVoo, 
            &vetorVoos[i].ehRegular, 
            &vetorVoos[i].diaSemana, 
            &vetorVoos[i].poltronasDisponiveis, 
            &vetorVoos[i].distancia);
    }
    fclose (arquivoVoos);
    return vetorVoos;
}