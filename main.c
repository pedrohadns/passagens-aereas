#include "menus.h"
// Grupo: Pedro Henrique Alves do Nascimento, Mauricio Zanetti Neto, Silvio Eduardo Bellinazzi de Andrade
#ifdef _WIN32
void imprimirLogo ();

int main (void){
    setlocale (LC_ALL, "Portuguese");

    FILE *arquivoVoos = fopen ("voos.dat", "r");
    quantidadeVoos = obterCodigoVooAnterior (arquivoVoos) + 1; // Somo um pois começa do 0
    fclose (arquivoVoos);
    vetorVoos = criarVetorVoos (quantidadeVoos);
    FILE *arquivoFuncionarios = fopen ("funcionarios.dat", "r");
    quantidadeFuncionarios = obterCodigoVooAnterior (arquivoFuncionarios) + 1;
    fclose (arquivoFuncionarios);
    funcionarios_cadastrados = criarVetorFuncionarios (quantidadeFuncionarios);
    
    imprimirLogo ();
    printf ("\nSeja bem vindo(a)!\n");
    menu ();

    free (vetorVoos);
    free (funcionarios_cadastrados);
    return EXIT_SUCCESS;
}

void imprimirLogo (){
    printf("\033[31m");
    printf("   _____ ______ _____  ____  ______ _____  _    _  _____            _____ _____  _      _____ _   _ ______  _____ \n");
    printf("  / ____|  ____|  __ \\|  _ \\|  ____|  __ \\| |  | |/ ____|     /\\   |_   _|  __ \\| |    |_   _| \\ | |  ____|/ ____|\n");
    printf(" | |    | |__  | |__) | |_) | |__  | |__) | |  | | (___      /  \\    | | | |__) | |      | | |  \\| | |__  | (___  \n");
    printf(" | |    |  __| |  _  /|  _ <|  __| |  _  /| |  | |\\___ \\    / /\\ \\   | | |  _  /| |      | | | . ` |  __|  \\___ \\ \n");
    printf(" | |____| |____| | \\ \\| |_) | |____| | \\ \\| |__| |____) |  / ____ \\ _| |_| | \\ \\| |____ _| |_| |\\  | |____ ____) |\n");
    printf("  \\_____|______|_|  \\_\\____/|______|_|  \\_\\\\____/|_____/  /_/    \\_\\_____|_|  \\_\\______|_____|_| \\_|______|_____/ \n");
    printf("\033[0m");
}
#else
int main (void){
    setlocale (LC_ALL, "Portuguese");
    printf ("O sistema só pode rodar em sistemas Windows.\n");
    return EXIT_FAILURE;
}
#endif