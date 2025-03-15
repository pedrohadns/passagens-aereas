#include "pagamento.h"
#include "dias_do_ano.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// objetivos ainda não colocados: quero que o cpf,rg e email do comprador tenha um limite, mas vc pode colocar qualquer coisa que é validado.
typedef struct {
    char nome[50];
    char cargo[10]; // "gerente" ou "vendedor"
    char matricula[12]; // 11 dígitos + terminador de string
} Funcionario;

// jesus que trem dificil de verificar, pq o cara teve essa ideia maldita
Funcionario funcionarios[] = {
    {"Silvio", "vendedor", "12345678901"},
    {"Pedro", "gerente", "98765432102"},
    {"Mauricio", "vendedor", "19283746503"}
};


#define NUM_FUNCIONARIOS (sizeof(funcionarios) / sizeof(funcionarios[0]))

// validar funcionário( muito legal isso, obrigado oberlan que me explicou 1x)
int validarFuncionario(char *matricula, char *nome, char *cargo) {
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        if (strcmp(funcionarios[i].matricula, matricula) == 0 &&
            strcmp(funcionarios[i].nome, nome) == 0 &&
            strcmp(funcionarios[i].cargo, cargo) == 0) {
            return 1; // PQ É TÂO DIFICIL A VIDA??? aqui o 1 é para o funcionario valido 
        }
    }
    return 0; //  trabalhador inválido(faz o L), deu uns 30 erros, mas funciona dps da fé quase ir embora 
}

// Função para obter o fator do dia (obrigado google, por ter me feito conhecer alguem que já fez algo parecido)
double obterFatorDia(int dia, int mes, int ano) {
    if (ehFeriado(dia, mes, ano)) return 3.56;
    if (ehFinalDeSemana(dia, mes, ano)) return 1.21;
    return 1.00;
}

// a unica parte que eu entendi daquele corno, mas obrigado gpt por ter corrigido o erro bobo, aqui acontece a magia de calcular preço
double calcularPreco(double distancia, int diferencaDatas, double ocupacao, int diasRetorno, int dia, int mes, int ano) {
    double precoPorMilha = (distancia <= 500) ? 0.36 : (distancia <= 800) ? 0.29 : 0.21;
    double fatorDia = obterFatorDia(dia, mes, ano);
    return distancia * precoPorMilha * fatorDia;
}

// processar pagamento (Deus éainda existe?? se eu terminar isso é pq sim) atualização: existe
void realizarPagamento(Pagamento *pagamento, double precoTotal) {
    char metodo[20];
    printf("Valor total: R$ %.2f\n", precoTotal);
    printf("Escolha a forma de pagamento (dinheiro, credito, debito): ");
    scanf("%s", metodo);

    if (strcmp(metodo, "dinheiro") == 0) {
        char matricula[12], nome[50], cargo[10];
        printf("Informe a matrícula do funcionário: ");
        scanf("%s", matricula);
        printf("Informe o nome do funcionário: ");
        scanf("%s", nome);
        printf("Informe o cargo: ");
        scanf("%s", cargo); //pq vc da tanto erro???

        if (!validarFuncionario(matricula, nome, cargo)) {
            printf("Erro: Dados do funcionário incorretos! Venda cancelada.\n");
            strcpy(pagamento->metodoPagamento, "");  // obrigado gpt, não conseguiria sem vc te amo 
            return;  
        }
    }

    strcpy(pagamento->metodoPagamento, metodo);
    pagamento->preco = precoTotal;
    printf("Pagamento realizado com sucesso via %s!\n", pagamento->metodoPagamento);
}

// registo de pagamento no arquivo (facil MUITO facil)
void registrarPagamentoArquivo(Pagamento *pagamento, Passageiro *passageiro) {
    FILE *arquivo = fopen("pagamentos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de pagamentos.\n");
        return;
    }
    fprintf(arquivo, "Passageiro: %s, CPF: %s, Valor: R$ %.2f, Metodo: %s\n", 
            passageiro->nome, passageiro->cpf, pagamento->preco, pagamento->metodoPagamento);
    fclose(arquivo);
    printf("Pagamento registrado com sucesso!\n");
}

// cadastro de passageiro(pq tem que ser dificil jesus)
void cadastrarPassageiro(Passageiro *passageiro) {
    printf("Nome: ");
    scanf("%s", passageiro->nome);
    printf("RG: ");
    scanf("%s", passageiro->rg);
    printf("CPF: ");
    scanf("%s", passageiro->cpf);
    printf("Telefone: ");
    scanf("%s", passageiro->telefone);
    printf("Email: ");
    scanf("%s", passageiro->email);
    printf("Bagagem extra (1 para SIM, 0 para NAO): ");
    scanf("%d", &passageiro->bagagemExtra);
}

int main() {
    Passageiro passageiro;
    Pagamento pagamento;
    double precoTotal, distancia, ocupacao;
    int diferencaDatas, diasRetorno, dia, mes, ano;

    // infos do usuario sobre o voo 
    printf("Informe a distância da viagem: ");
    scanf("%lf", &distancia);
    printf("Informe a data do voo (DD MM AAAA): ");// pfv digite 1 e da enter
    scanf("%d %d %d", &dia, &mes, &ano);
    printf("Informe a diferença de dias até o voo: ");
    scanf("%d", &diferencaDatas);
    printf("Qual a porcentagem de ocupação do voo? ");
    scanf("%lf", &ocupacao);
    printf("Informe os dias para retorno: ");
    scanf("%d", &diasRetorno);

    precoTotal = calcularPreco(distancia, diferencaDatas, ocupacao, diasRetorno, dia, mes, ano);
    printf("Valor: R$ %.2f\n", precoTotal);

    cadastrarPassageiro(&passageiro);
    realizarPagamento(&pagamento, precoTotal);

    // **CORREÇÃO: DEUS QUE TREM DIFICIL JESUS AMADOOOOOOOOOOOOOO**
    if (strcmp(pagamento.metodoPagamento, "") != 0) {  
        registrarPagamentoArquivo(&pagamento, &passageiro);
    }
}
