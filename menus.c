#include "menus.h"

void menu (){
    int opcao;
    do{
        printf ("\n[1] Configurações\n");
        printf ("[2] Vendas\n");
        printf ("[3] Sair\n");
        printf ("Digite a opção desejada: ");
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
                printf ("Opção inválida!\n");
                break;
        }
    } while (opcao != 3);
}

void configuracoes (){
    int opcao;
    do{
        printf ("\n[4] Cadastrar voo\n");
        printf ("[5] Cadastrar passageiro\n");
        printf ("[6] Cadastrar funcionário\n");
        printf ("[7] Alterar dados funcionário\n");
        printf ("[8] Voltar\n");
        printf ("Digite a opção desejada: ");
        scanf ("%d", &opcao);
        getchar ();
        Passageiro novo_passageiro;
        Funcionario funcionario_autorizado;
        switch (opcao){
            case 4:
                incluirVoo ();
                FILE *arquivoVoos = fopen ("voos.dat", "r");
                quantidadeVoos = obterCodigoVooAnterior (arquivoVoos);
                fclose (arquivoVoos);
                vetorVoos = criarVetorVoos (quantidadeVoos);
                break;
            case 5:
                cadastrarPassageiro (&novo_passageiro);
                break;
            case 6:
                printf ("Digite seu nome: ");
                leString (funcionario_autorizado.nome, 50);
                printf ("Digite sua matrícula (CPF sem pontos): ");
                leString (funcionario_autorizado.matricula, 12);
                printf ("Digite seu cargo: ");
                leString (funcionario_autorizado.cargo, 10);
                if (validarFuncionario (funcionario_autorizado.matricula, funcionario_autorizado.nome, funcionario_autorizado.cargo) && strcmp (funcionario_autorizado.cargo, "GERENTE") == 0){
                    incluirFuncionario ();
                    break;
                }
                else{
                    printf ("Você não tem permissão para fazer isso.\n");
                    break;
                }
            case 7:
                printf ("Digite seu nome: ");
                leString (funcionario_autorizado.nome, 50);
                printf ("Digite sua matrícula (CPF sem pontos): ");
                leString (funcionario_autorizado.matricula, 12);
                printf ("Digite seu cargo: ");
                leString (funcionario_autorizado.cargo, 10);
                if (validarFuncionario (funcionario_autorizado.matricula, funcionario_autorizado.nome, funcionario_autorizado.cargo) && strcmp (funcionario_autorizado.cargo, "GERENTE") == 0){
                    alterarFuncionario ();
                    break;
                }
                else{
                    printf ("Você não tem permissão para fazer isso.\n");
                    break;
                }
            case 8:
                break;
            default:
                printf ("Opção inválida!\n");
                break;
        }
    } while (opcao != 8);
}

void vendas (){
    int opcao;
    do{
        printf ("\n[9] Realizar venda\n");
        printf ("[10] Voltar\n");
        printf ("Digite a opção desejada: ");
        scanf ("%d", &opcao);
        getchar ();
        switch (opcao){
            case 9:
                realizarVenda ();
                // Parte de pagamentos e ticket;
                break;
            case 10:
                break;
            default:
                printf ("Opção inválida!\n");
                break;
        }
    } while (opcao != 10);
}

int calculaDiaSemana (int dia, int mes, int ano){
    int YY, codigoAno, codigoMes, codigoSeculo = 6, ehBisssexto = 0;
    YY = ano % 2000;
    codigoAno = (YY + (YY / 4)) % 7;
    switch (mes){
        case 1:
        case 10:
            codigoMes = 0;
            break;
        case 2:
        case 3:
        case 11:
            codigoMes = 3;
            break;
        case 4:
        case 7:
            codigoMes = 6;
            break;
        case 5:
            codigoMes = 1;
            break;
        case 6:
            codigoMes = 4;
            break;
        case 8:
            codigoMes = 2;
            break;
        case 9:
        case 12:
            codigoMes = 5;
            break;
        default:
            codigoMes = -1;
            break;
    }
    if (((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && (mes == 1 || mes == 2)){
        ehBisssexto = 1;
    }
    return (codigoAno + codigoMes + codigoSeculo + dia - ehBisssexto) % 7 + 1;
}

void visualizarVoos (char *Origem, char *Destino, int dia, int mes, int ano, int *flagVoosDisponiveis){
    for (unsigned int i = 0; i < quantidadeVoos; i++){
        if (strcmp (vetorVoos[i].origem.cidade, Origem) == 0 && strcmp (vetorVoos[i].destino.cidade, Destino) == 0){ // Mostra somente os voos da rota desejada
            Matriz m;
            carregar_assentos (&m, vetorVoos[i].codigoRota, dia, mes, ano);
            int numAssentosDisponiveis = numeroAssentosDisponiveis (&m);
            if (numAssentosDisponiveis == 0){ // Se não houver assentos disponíveis, não exibe o voo
                continue;
            }
            if (vetorVoos[i].diaSemana != calculaDiaSemana (dia, mes, ano) && (vetorVoos[i].ehRegular == 'n' || vetorVoos[i].ehRegular == 'N')){
                continue;
            }
            *flagVoosDisponiveis = 1;
            printf ("Rota: %s\n", vetorVoos[i].nomeRota);
            printf ("Código do voo: %d\n", vetorVoos[i].codigoRota);
            printf ("Horário: %02d:%02d\n", vetorVoos[i].horaVoo, vetorVoos[i].minutoVoo);
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
                        printf ("Terça-feira\n");
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
                        printf ("Sábado\n");
                        break;
                    default:
                        printf ("Dia da semana inválido\n");
                        break;
                }
            }
            printf ("Assentos disponíveis: %d\n", numAssentosDisponiveis);
            printf ("Distância: %.2lf milhas\n", vetorVoos[i].distancia);
            printf ("\n");
        }
    }
    if (*flagVoosDisponiveis == 0){
        printf ("Não há voos disponíveis para a rota %s - %s\n", Origem, Destino);
    }
}

void realizarVenda (){
    char cidadeOrigem[50], cidadeDestino[50];
    int flagVoosDisponiveis = 0, dia, mes, ano;

    printf ("Digite a data do voo (dd mm aaaa): ");
    scanf ("%d", &dia);
    scanf ("%d", &mes);
    scanf ("%d", &ano);
    printf ("Digite a cidade de origem: ");
    fflush (stdin);
    fgets (cidadeOrigem, 50, stdin);
    cidadeOrigem[strcspn (cidadeOrigem, "\n")] = '\0';
    printf ("Digite a cidade de destino: ");
    fgets (cidadeDestino, 50, stdin);
    cidadeDestino[strcspn (cidadeDestino, "\n")] = '\0';
    visualizarVoos (cidadeOrigem, cidadeDestino, dia, mes, ano, &flagVoosDisponiveis);
    if (flagVoosDisponiveis == 0){
        return;
    }
    printf ("Digite o código do voo desejado: ");
    int codigoVoo;
    scanf (" %d", &codigoVoo);
    printf ("Exibindo assentos disponíveis...\n");
    Matriz m;
    carregar_assentos (&m, codigoVoo, dia, mes, ano);
    reservar_assento (&m, codigoVoo, dia, mes, ano);
    // Pagamentos...
    Passageiro passageiro_atual;
    Pagamento pagamento_atual;
    cadastrarPassageiro (&passageiro_atual);
    int sucessoPagamento = realizarPagamento (passageiro_atual, &pagamento_atual, vetorVoos[codigoVoo], dia, mes, ano);

    if (!sucessoPagamento){gerarEticketCompleto (passageiro_atual, pagamento_atual, vetorVoos[codigoVoo], dia, mes, ano);}
}