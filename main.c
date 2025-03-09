#include "menus.h"

int main(void){
    setlocale (LC_ALL, "Portuguese");

    FILE *arquivoVoos = fopen ("voos.dat", "r");
    quantidadeVoos = obterCodigoVooAnterior (arquivoVoos);
    fclose (arquivoVoos);
    vetorVoos = criarVetorVoos (quantidadeVoos);

    menu ();

    free (vetorVoos);
    return EXIT_SUCCESS;
}