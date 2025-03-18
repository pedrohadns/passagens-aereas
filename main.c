#include "menus.h"
// Grupo: Pedro Henrique Alves do Nascimento, Mauricio Zanetti Neto, Silvio Eduardo Belinazzi
#ifdef _WIN32
int main (void){
    setlocale (LC_ALL, "Portuguese");

    FILE *arquivoVoos = fopen ("voos.dat", "r");
    quantidadeVoos = obterCodigoVooAnterior (arquivoVoos);
    fclose (arquivoVoos);
    vetorVoos = criarVetorVoos (quantidadeVoos);

    menu ();

    free (vetorVoos);
    return EXIT_SUCCESS;
}
#else
int main (void){
    setlocale (LC_ALL, "Portuguese");
    printf ("O sistema só pode rodar em sistemas Windows.\n");
    return EXIT_FAILURE;
}
#endif