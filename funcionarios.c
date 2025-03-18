#include "funcionarios.h"

void escreveArquivoFuncionarios (FILE *arquivo, Funcionario funcionario_sendo_escrito){
    fseek (arquivo, 0, SEEK_END);
    char numeroConvertidoString[50];
    sprintf (numeroConvertidoString, "%d;", funcionario_sendo_escrito.id);
    fputs (numeroConvertidoString, arquivo);
    imprimeStringnoArquivo (arquivo, funcionario_sendo_escrito.nome);
    imprimeStringnoArquivo (arquivo, funcionario_sendo_escrito.matricula);
    fputs (strcat (funcionario_sendo_escrito.cargo, "\n"), arquivo);
}

void capitalizarString (char *str){
    for (int i = 0; i < strlen (str); i++){
        str[i] = toupper (str[i]);
    }
}

void incluirFuncionario (){
    FILE *arquivo = fopen ("funcionarios.dat", "a+");
    if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo dos funcionários.\n");
        return;
    }
    Funcionario funcionario_sendo_cadastrado;
    funcionario_sendo_cadastrado.id = obterCodigoVooAnterior (arquivo) + 1; // Usa a função para saber o número de funcionários
    printf ("Digite o nome do funcionário: ");
    leString (funcionario_sendo_cadastrado.nome, 50);
    capitalizarString (funcionario_sendo_cadastrado.nome);
    printf ("Digite o CPF do funcionário (somente os números): ");
    leString (funcionario_sendo_cadastrado.matricula, 12);
    printf ("Digite o cargo do funcionário (gerente ou vendedor): ");
    leString (funcionario_sendo_cadastrado.cargo, 10);
    capitalizarString (funcionario_sendo_cadastrado.cargo);
    escreveArquivoFuncionarios (arquivo, funcionario_sendo_cadastrado);
    fclose (arquivo);
    quantidadeFuncionarios++;
    funcionarios_cadastrados = criarVetorFuncionarios (quantidadeFuncionarios);
}

Funcionario *criarVetorFuncionarios (int quantidadeFuncionarios){
    FILE *arquivoFuncionarios = fopen ("funcionarios.dat", "r");
    if (arquivoFuncionarios == NULL){
        printf ("Erro ao abrir o arquivo dos funcionários.\n");
        return NULL;
    }
    Funcionario *funcionarios_cadastrados_funcao;
    funcionarios_cadastrados_funcao = (Funcionario *) malloc (quantidadeFuncionarios * sizeof (Funcionario));
    if (funcionarios_cadastrados_funcao == NULL){
        printf ("Erro ao alocar memória.\n");
        return NULL;
    }
    
    for (int i = 0; i < quantidadeFuncionarios; i++){
        fscanf (arquivoFuncionarios, "%i;%50[^;];%12[^;];%10[^\n]",
                &funcionarios_cadastrados_funcao[i].id,
                funcionarios_cadastrados_funcao[i].nome,
                funcionarios_cadastrados_funcao[i].matricula,
                funcionarios_cadastrados_funcao[i].cargo);
    }
    fclose (arquivoFuncionarios);
    return funcionarios_cadastrados_funcao;
}

void alterarFuncionario (){
    int opcaoAlteracao;
    char nomeSendoAlterado[50], matriculaSendoAlterado[12];
    printf ("Digite o nome do funcionário que deseja alterar: ");
    leString (nomeSendoAlterado, 50);
    capitalizarString (nomeSendoAlterado);
    printf ("Digite a matrícula do funcionário que deseja alterar: ");
    leString (matriculaSendoAlterado, 12);
    for (int i = 0; i < quantidadeFuncionarios; i++){
        if (strcmp (funcionarios_cadastrados[i].nome, nomeSendoAlterado) == 0 && 
            strcmp (funcionarios_cadastrados[i].matricula, matriculaSendoAlterado) == 0){
            do{
                printf ("[1] Alterar nome\n[2] Alterar matrícula\n[3] Alterar cargo\nDigite a opção desejada: ");
                scanf ("%d", &opcaoAlteracao);
                switch (opcaoAlteracao){
                    case 1:
                        printf ("Digite o novo nome: ");
                        leString (funcionarios_cadastrados[i].nome, 50);
                        capitalizarString (funcionarios_cadastrados[i].nome);
                        break;
                    case 2:
                        printf ("Digite a nova matrícula: ");
                        leString (funcionarios_cadastrados[i].matricula, 12);
                        break;
                    case 3:
                        printf ("Digite o novo cargo: ");
                        leString (funcionarios_cadastrados[i].cargo, 10);
                        capitalizarString (funcionarios_cadastrados[i].cargo);
                        break;
                    default:
                        printf ("Opção inválida, tente novamente.\n");
                        break;
                }
            } while (opcaoAlteracao != 1 && opcaoAlteracao != 2 && opcaoAlteracao != 3);
            escreveVetorInteiroFuncionarios ();
            return;
        }
    }
    printf ("Não existe funcionário com esses dados.\n");
}

void escreveVetorInteiroFuncionarios (){
    FILE *arquivo = fopen ("funcionarios.dat", "w");
    if (arquivo == NULL){
        printf ("Erro ao abrir arquivo.\n");
        return;
    }
    for (int i = 0; i < quantidadeFuncionarios; i++){
        fprintf (arquivo, "%d;%s;%s;%s\n", funcionarios_cadastrados[i].id, funcionarios_cadastrados[i].nome, funcionarios_cadastrados[i].matricula, funcionarios_cadastrados[i].cargo);
    }
    fclose (arquivo);
}