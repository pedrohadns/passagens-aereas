#include "menus.h"

void menu (){
    int opcao;
    do{
        printf ("\n[1] Configura��es\n");
        printf ("[2] Vendas\n");
        printf ("[3] Sair\n");
        printf ("Digite a op��o desejada: ");
        scanf ("%d", &opcao);
        getchar ();
        switch (opcao){
            case 1:
                configuracoes ();
                break;
            case 2:
                vendas ();
                break;
            case 3:
                break;
            default:
                printf ("Op��o inv�lida!\n");
                break;
        }
    } while (opcao != 3);
}

void configuracoes (){
    int opcao;
    do{
        printf ("\n[4] Cadastrar voo\n");
        printf ("[5] Cadastrar passageiro\n");
        printf ("[6] Alterar dados passageiro\n");
        printf ("[7] Cadastrar funcion�rio\n");
        printf ("[8] Alterar dados funcion�rio\n");
        printf ("[9] Voltar\n");
        printf ("Digite a op��o desejada: ");
        scanf ("%d", &opcao);
        getchar ();
        switch (opcao){
            case 4:
                incluirVoo ();
                FILE *arquivoVoos = fopen ("voos.dat", "r");
                quantidadeVoos = obterCodigoVooAnterior (arquivoVoos);
                fclose (arquivoVoos);
                vetorVoos = criarVetorVoos (quantidadeVoos);
                break;
            case 5:
               // incluirPassageiro ();
                break;
            case 6:
                //alterarPassageiro ();
                break;
            case 7:
                //incluirFuncionario ();
                break;
            case 8:
                //alterarFuncionario ();
                break;
            case 9:
                break;
            default:
                printf ("Op��o inv�lida!\n");
                break;
        }
    } while (opcao != 9);
}

void vendas (){
    int opcao;
    do{
        printf ("\n[10] Realizar venda\n");
        printf ("[11] Voltar\n");
        printf ("Digite a op��o desejada: ");
        scanf ("%d", &opcao);
        getchar ();
        switch (opcao){
            case 10:
                realizarVenda ();
                break;
            case 11:
                break;
            default:
                printf ("Op��o inv�lida!\n");
                break;
        }
    } while (opcao != 11);
}

void visualizarVoos (){
    for (unsigned int i = 0; i < quantidadeVoos; i++){
        printf ("Rota: %s\n", vetorVoos[i].nomeRota);
        printf ("C�digo do voo: %d\n", vetorVoos[i].codigoRota);
        printf ("Hor�rio: %02d:%02d\n", vetorVoos[i].horaVoo, vetorVoos[i].minutoVoo);
        if (vetorVoos[i].ehRegular == 'n' || vetorVoos[i].ehRegular == 'N'){
            printf ("Dia da Semana: ");
            switch (vetorVoos[i].diaSemana){
                case 1:
                    printf ("Domingo\n");
                    break;
                case 2:
                    printf ("Segunda-feira\n");
                    break;
                case 3:
                    printf ("Ter�a-feira\n");
                    break;
                case 4:
                    printf ("Quarta-feira\n");
                    break;
                case 5:
                    printf ("Quinta-feira\n");
                    break;
                case 6:
                    printf ("Sexta-feira\n");
                    break;
                case 7:
                    printf ("S�bado\n");
                    break;
                default:
                    printf ("Dia da semana inv�lido\n");
                    break;
            }
        }
        printf ("Poltronas dispon�veis: %d\n", vetorVoos[i].poltronasDisponiveis);
        printf ("Dist�ncia: %.2lf milhas\n", vetorVoos[i].distancia);
        printf ("\n");
    }
}

void realizarVenda (){
    char opcaoVisualizar;
    printf ("Deseja visualizar os voos dispon�veis? (s/n): ");
    scanf (" %c", &opcaoVisualizar); 
    if (opcaoVisualizar == 's' || opcaoVisualizar == 'S'){
        visualizarVoos ();
    }
    printf ("Digite o c�digo do voo desejado: ");
    unsigned int codigoVoo;
    scanf ("%d", &codigoVoo);
    getchar ();
    // Etapas 2 e 3...
}