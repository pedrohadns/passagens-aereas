#include "pagamento.h"

Funcionario funcionarios[] = {
    {"SILVIO", "VENDEDOR", "12345678901"},
    {"PEDRO", "GERENTE", "98765432102"},
    {"MAURICIO", "VENDEDOR", "19283746503"},
    {"PROFESSOR", "GERENTE", "123"}
};

#define NUM_FUNCIONARIOS (sizeof(funcionarios) / sizeof(funcionarios[0]))

int validarFuncionario(char *matricula, char *nome, char *cargo) {
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        for (int j = 0; j < strlen (nome); j++){
            nome[j] = toupper (nome[j]);
        }
        for (int j = 0; j < strlen (cargo); j++){
            cargo[j] = toupper (cargo[j]);
        }

        if (strcmp(funcionarios[i].matricula, matricula) == 0 &&
            strcmp(funcionarios[i].nome, nome) == 0 &&
            strcmp(funcionarios[i].cargo, cargo) == 0) {
            return 1;
        }
    }
    return 0;
}

double obterFatorDia (int dia, int mes, int ano){
    if (ehFeriado (dia, mes, ano)){
        return 3.56;
    }
    else if (ehFinalDeSemana (dia, mes, ano)){
        return 1.21;
    }
    else{
        return 1.0;
    }
}

int calcularDiasAteVoo(int dia_voo, int mes_voo, int ano_voo) {
    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);

    struct tm data_voo = {0};
    data_voo.tm_year = ano_voo - 1900;
    data_voo.tm_mon = mes_voo - 1;
    data_voo.tm_mday = dia_voo;

    time_t timestamp_voo = mktime(&data_voo);
    double diferenca = difftime(timestamp_voo, agora);
    return (int)(diferenca / (60 * 60 * 24)) + 1;
}

double calcularFatorPER(int dias_ate_voo) {
    if (dias_ate_voo <= 3) return 4.52;
    else if (dias_ate_voo <= 6) return 3.21;
    else if (dias_ate_voo <= 10) return 2.25;
    else if (dias_ate_voo <= 15) return 1.98;
    else if (dias_ate_voo <= 20) return 1.78;
    else if (dias_ate_voo <= 30) return 1.65;
    else return 1.45;
}

double calcularFatorRET(int dias_retorno) {
    if (dias_retorno <= 2) return 1.09;
    else if (dias_retorno <= 5) return 1.05;
    else if (dias_retorno <= 8) return 1.02;
    else return 1.00;
}

double calcularFatorPROC(double ocupacao_percentual) {
    if (ocupacao_percentual > 90.0) return 0.75;
    else if (ocupacao_percentual >= 70.0) return 0.85;
    else if (ocupacao_percentual >= 60.0) return 0.95;
    else if (ocupacao_percentual >= 40.0) return 1.00;
    else if (ocupacao_percentual >= 20.0) return 1.15;
    else if (ocupacao_percentual >= 10.0) return 1.20;
    else return 1.35;
}

double calcularPrecoVoo(Voo voo, int dia_voo, int mes_voo, int ano_voo, int dias_retorno) {
    int dias_ate_voo = calcularDiasAteVoo(dia_voo, mes_voo, ano_voo);
    Matriz m;
    carregar_assentos (&m, voo.codigoRota, dia_voo, mes_voo, ano_voo);
    int numAssentosDisponiveis = numeroAssentosDisponiveis (&m);
    double ocupacao = (( voo.poltronasDisponiveis - numAssentosDisponiveis ) * 100.0) / voo.poltronasDisponiveis;
    
    double preco_por_milha;
    if (voo.distancia <= 500) preco_por_milha = 0.36;
    else if (voo.distancia <= 800) preco_por_milha = 0.29;
    else preco_por_milha = 0.21;

    return voo.distancia * preco_por_milha *
           calcularFatorPER(dias_ate_voo) *
           obterFatorDia(dia_voo, mes_voo, ano_voo) *
           calcularFatorRET(dias_retorno) *
           calcularFatorPROC(ocupacao);
}

int realizarPagamento(Passageiro passageiro, Pagamento *pagamento, Voo voo, int dia_voo, int mes_voo, int ano_voo) {
    int dias_retorno = 0;
    int eh_ida_volta;
    printf("A viagem inclui retorno? (1-Sim/0-Não): ");
    scanf("%d", &eh_ida_volta);
    
    if(eh_ida_volta) {
        int diaRetorno, mesRetorno, anoRetorno;
        printf ("Digite a data de retorno (dd mm aaaa): ");
        scanf ("%d", &diaRetorno);
        scanf ("%d", &mesRetorno);
        scanf ("%d", &anoRetorno);
        struct tm data1 = {0}, data2 = {0};
    
        // Configurar a primeira data
        data1.tm_mday = dia_voo;
        data1.tm_mon = mes_voo - 1;
        data1.tm_year = ano_voo - 1900;

        // Configurar a segunda data
        data2.tm_mday = diaRetorno;
        data2.tm_mon = mesRetorno - 1;
        data2.tm_year = anoRetorno - 1900;

        // Converter para time_t
        time_t tempo1 = mktime(&data1);
        time_t tempo2 = mktime(&data2);

        if (tempo1 == -1 || tempo2 == -1) {
            printf("Erro ao converter datas.\n");
            Matriz m;
            carregar_assentos (&m, voo.codigoRota, dia_voo, mes_voo, ano_voo);
            cancelar_reserva_assento (&m, voo.codigoRota, dia_voo, mes_voo, ano_voo, escolha_assento);
            return 1;
        }

        dias_retorno = (int)difftime(tempo2, tempo1) / (60 * 60 * 24);
    }

    double precoTotal = calcularPrecoVoo(voo, dia_voo, mes_voo, ano_voo, dias_retorno);
    printf("\n=== RESUMO DO PAGAMENTO ===\n");
    printf("Distância: %.2f milhas\n", voo.distancia);
    printf("Data do voo: %02d/%02d/%04d\n", dia_voo, mes_voo, ano_voo);
    printf("Preço total: R$ %.2f\n\n", precoTotal);

    char metodo[20];
    int tentativas = 3;
    
    while(tentativas > 0) {
        printf("Métodos disponíveis:\n");
        printf("1. Dinheiro\n2. Cartão de crédito\n3. Cartão de débito\n");
        printf("Escolha o método (digite o número): ");
        scanf(" %19[^\n]s", metodo);

        if(strcmp(metodo, "1") == 0) {
            char matricula[12], nome[50], cargo[10];
            printf("\n=== Validação do Funcionário ===\n");
            printf("Matrícula: ");
            scanf(" %11[^\n]s", matricula);
            printf("Nome: ");
            scanf(" %49[^\n]s", nome);
            printf("Cargo: ");
            scanf(" %9[^\n]s", cargo);

            if(validarFuncionario(matricula, nome, cargo)) {
                strcpy(pagamento->metodoPagamento, "Dinheiro");
                break;
            } else {
                printf("Funcionário não autorizado! Tentativas restantes: %d\n", --tentativas);
            }
        }
        else if(strcmp(metodo, "2") == 0) {
            strcpy(pagamento->metodoPagamento, "Crédito");
            break;
        }
        else if(strcmp(metodo, "3") == 0) {
            strcpy(pagamento->metodoPagamento, "Débito");
            break;
        }
        else {
            printf("Opção inválida! Tentativas restantes: %d\n", --tentativas);
        }
    }

    if(tentativas == 0) {
        printf("Pagamento cancelado por excesso de tentativas!\n");
        strcpy(pagamento->metodoPagamento, "");

        Matriz m;
        carregar_assentos (&m, voo.codigoRota, dia_voo, mes_voo, ano_voo);
        cancelar_reserva_assento (&m, voo.codigoRota, dia_voo, mes_voo, ano_voo, escolha_assento);
        return 1;
    }

    pagamento->preco = precoTotal;

    printf("\n=== PAGAMENTO CONFIRMADO ===\n");
    printf("Método: %s\n", pagamento->metodoPagamento);
    printf("Valor: R$ %.2f\n", pagamento->preco);
    registrarPagamentoArquivo (*pagamento, passageiro, voo, dia_voo, mes_voo, ano_voo);
    return 0;
}

void registrarPagamentoArquivo(Pagamento pagamento, Passageiro passageiro, Voo voo, int dia, int mes, int ano) {
    FILE *arquivo = fopen("pagamentos.dat", "a");
    if(arquivo == NULL) {
        printf("Erro ao registrar pagamento!\n");
        return;
    }

    fprintf(arquivo, "=== Ticket %s ===\n", passageiro.cpf);
    fprintf(arquivo, "Passageiro: %s\n", passageiro.nome);
    fprintf(arquivo, "Voo: %s - %s\n", 
           voo.origem.codigoAeroporto, 
           voo.destino.codigoAeroporto);
    fprintf(arquivo, "Data: %02d/%02d/%04d\n", dia, mes, ano);
    fprintf(arquivo, "Valor: R$ %.2f\n", pagamento.preco);
    fprintf(arquivo, "Metodo: %s\n\n", pagamento.metodoPagamento);
    
    fclose(arquivo);
}

void cadastrarPassageiro(Passageiro *passageiro) {
    printf("\n=== DADOS DO PASSAGEIRO ===\n");
    printf("Nome completo: ");
    scanf(" %[^\n]49s", passageiro->nome);
    
    printf("CPF (apenas números): ");
    scanf(" %11[^\n]s", passageiro->cpf);
    
    printf("RG (apenas números): ");
    scanf(" %9[^\n]s", passageiro->rg);
    
    printf("Data de nascimento (DDMMAAAA): ");
    scanf(" %8[^\n]s", passageiro->dataNascimento);
    
    printf("Telefone (com DDD): ");
    scanf(" %14[^\n]s", passageiro->telefone);
    
    printf("E-mail: ");
    scanf(" %49[^\n]s", passageiro->email);
    
    printf("Bagagem extra? (1-Sim/0-Não): ");
    scanf("%d", &passageiro->bagagemExtra);
}