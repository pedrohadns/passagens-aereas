#include "rota.h"


int main(void){
    setlocale (LC_ALL, "Portuguese");

    incluirVoo ();
    FILE *arquivoVoos = fopen ("voos.dat", "r");
    unsigned int quantidadeVoos = obterCodigoVooAnterior (arquivoVoos);
    fclose (arquivoVoos);
    Voo *vetorVoos = criarVetorVoos (quantidadeVoos);

    free (vetorVoos);
    return EXIT_SUCCESS;
}