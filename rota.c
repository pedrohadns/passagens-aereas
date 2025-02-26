#include "rota.h"

unsigned int obterCodigoVooAnterior (FILE *arquivo){
    unsigned int codigoRotaAnterior;
    fseek (arquivo, 0, SEEK_END);
    if (ftell (arquivo) == 0){
        codigoRotaAnterior = 0;
    } else {
        fseek (arquivo, -sizeof (Voo), SEEK_END);
        fread (&codigoRotaAnterior, sizeof (unsigned int), 1, arquivo);
    }
    return codigoRotaAnterior;
}

void cadastrarAeroporto (Aeroporto *aeroporto_sendo_cadastrado, char origemOuDestino){
    char opcao[8];
    if (origemOuDestino == 'o'){
        strcpy (opcao, "origem");
    }
    else if (origemOuDestino == 'd'){
        strcpy (opcao, "destino");
    }
    printf ("Digite o código do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->codigoAeroporto, 4);
    printf ("Digite o nome do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->nomeAeroporto, 50);
    printf ("Digite a cidade do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->cidade, 50);
    printf ("Digite a UF do aeroporto de %s: ", opcao);
    leString (aeroporto_sendo_cadastrado->estado, 3);
}

void criarNomeAeroporto (char *strDestino, Voo rota){
    strcpy (strDestino, rota.origem.nomeAeroporto);
    strcat (strDestino, "[");
    strcat (strDestino, rota.origem.codigoAeroporto);
    strcat (strDestino, "] - ");
    strcat (strDestino, rota.destino.nomeAeroporto);
    strcat (strDestino, "[");
    strcat (strDestino, rota.destino.codigoAeroporto);
    strcat (strDestino, "]");
}

void incluirVoo (){
    FILE *arquivo = fopen ("voos.dat", "a+");
    if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo\n");
        return;
    }
    unsigned int codigoRotaAnterior;
    Voo novoVoo;

    voos = (Voo *)realloc (voos, qtdVoos + sizeof (Voo));
    if (voos == NULL){
        printf ("Erro ao alocar memória\n");
        return;
    }
    codigoRotaAnterior = obterCodigoVooAnterior (arquivo);
    novoVoo.codigoRota = codigoRotaAnterior + 1;
    cadastrarAeroporto (&novoVoo.origem, 'o');
    cadastrarAeroporto (&novoVoo.destino, 'd');
    criarNomeAeroporto (novoVoo.nomeRota, novoVoo);
}

void main(){
    incluirVoo ();
}