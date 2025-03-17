#include "gerarpdf.h"

void gerar_arquivo_latex(Voo voo, int dia, int mes, int ano, Passageiro passageiro_atual, Pagamento pagamento_atual, char *codigoPortao, int codigoEticket, const char *pasta, const char *nome_arquivo) {
    char caminho_arquivo[256];
    snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s\\%s", pasta, nome_arquivo);
    
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Gerando o conteúdo LaTeX do recibo de passagem aérea
    fprintf(arquivo, "\\documentclass[10pt]{article}\n");
    fprintf(arquivo, "\\usepackage[paperwidth=8cm, paperheight=20cm, top=5mm, bottom=5mm, left=5mm, right=5mm]{geometry}\n");
    fprintf(arquivo, "\\usepackage{graphicx}\n");
    fprintf(arquivo, "\\usepackage{xcolor}\n");
    fprintf(arquivo, "\\usepackage{tcolorbox}\n");
    fprintf(arquivo, "\\usepackage{dashrule}\n");
    fprintf(arquivo, "\\usepackage{inconsolata}\n");
    fprintf(arquivo, "\\usepackage{parskip}\n");
    fprintf(arquivo, "\\pagecolor[rgb]{0.98, 0.95, 0.82}\n");
    fprintf(arquivo, "\\pagestyle{empty}\n");

    fprintf(arquivo, "\\begin{document}\n");
    fprintf(arquivo, "\\ttfamily\n");
    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\textbf{\\Large RECIBO DE VENDA DE PASSAGEM AÉREA} \\\\[-2pt]\n");
    fprintf(arquivo, "    \\hdashrule[0.5ex]{45mm}{1pt}{1mm}\n");
    fprintf(arquivo, "\\end{center}\n");

    fprintf(arquivo, "\\textbf{Companhia Aérea:} Cerberus Airlines\\\\\n");
    fprintf(arquivo, "\\textbf{CNPJ:} 64.008.947/0001-21\\\\[1ex]\n");
    fprintf(arquivo, "\\textbf{Endereço:} BR 101, km 60, Bairro Litorâneo, São Mateus/ES\\\\[-2pt]\n");
    fprintf(arquivo, "\\textbf{Telefone:} (27) 3752-4666 \\\\\n");

    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\hdashrule[0.5ex]{45mm}{1pt}{1mm}\n");
    fprintf(arquivo, "\\end{center}\n");
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    fprintf(arquivo, "\\textbf{Data da Compra:} %02d/%02d/%04d \\hfill \\textbf{Hora:} %02d:%02d \\\\[2ex]\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, tm_info->tm_hour, tm_info->tm_min);
    fprintf(arquivo, "\\textbf{Voo:} %d \\hfill \\\\\n", voo.codigoRota);
    fprintf(arquivo, "\\textbf{Número do Bilhete:} %d \\\\[2ex]\n", codigoEticket);
    fprintf(arquivo, "\\textbf{Origem:} %s (%s) \\hfill \\\\\n", voo.origem.cidade, voo.origem.codigoAeroporto);
    fprintf(arquivo, "\\textbf{Destino:} %s (%s) \\\\[2ex]\n", voo.destino.cidade, voo.destino.codigoAeroporto);
    fprintf(arquivo, "\\textbf{Data do Voo:} %02d/%02d/%04d\\hfill \\\\\n", dia, mes, ano);
    fprintf(arquivo, "\\textbf{Hora de Partida:} %02d:%02d \\\\ \n", voo.horaVoo, voo.minutoVoo);
    fprintf(arquivo, "\\textbf{Portão de Embarque:} %s \\\\[2ex]\n", codigoPortao);

    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\begin{tabular}{p{4cm} c}\n");
    fprintf(arquivo, "        ------------------------ \\\\\n");
    fprintf(arquivo, "        \\textbf{Passageiro} & \\textbf{Valor} \\\\\n");
    fprintf(arquivo, "        ------------------------ \\\\\n");
    fprintf(arquivo, "        %s & %.2f \\\\\n", passageiro_atual.nome, pagamento_atual.preco);
    fprintf(arquivo, "        ------------------------ \\\\\n");
    fprintf(arquivo, "        \\textbf{Total} & \\textbf{%.2f} \\\\\n", pagamento_atual.preco);
    fprintf(arquivo, "        ------------------------ \\\\\n");
    fprintf(arquivo, "    \\end{tabular}\n");
    fprintf(arquivo, "\\end{center}\n");
    if (strcmp (pagamento_atual.metodoPagamento, "Dinheiro") == 0){
        fprintf(arquivo, "\\textbf{Forma de Pagamento:} %s \\\\\n", pagamento_atual.metodoPagamento);
    }
    else {fprintf(arquivo, "\\textbf{Forma de Pagamento:} Cartão de %s \\\\\n", pagamento_atual.metodoPagamento);}

    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\hdashrule[0.5ex]{45mm}{1pt}{1mm}\n");
    fprintf(arquivo, "\\end{center}\n");

    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\textbf{Obrigado pela sua compra!} \\\\\n");
    fprintf(arquivo, "    \\textbf{Desejamos uma boa viagem!} \\\\[2pt]\n");
    fprintf(arquivo, "    Mais informações no site \\\\[-2pt]\n");
    fprintf(arquivo, "    www.cerberusairlines.com \\\\\n");
    fprintf(arquivo, "\\end{center}\n");

    fprintf(arquivo, "\\begin{center}\n");
    fprintf(arquivo, "    \\hdashrule[0.5ex]{45mm}{1pt}{1mm}\n");
    fprintf(arquivo, "\\end{center}\n");

    fprintf(arquivo, "\\end{document}\n");

    fclose(arquivo);
}

void compilar_latex(const char *pasta, const char *nome_arquivo) {
    char comando[512];
    snprintf(comando, sizeof(comando), "cmd /c \"cd /d %s && pdflatex %s > nul 2>&1\"", pasta, nome_arquivo);
    
    int status = system(comando);
    if (status == -1) {
        perror("Erro ao compilar o arquivo LaTeX");
        exit(1);
    }
}

void limpar_diretorio(const char *pasta, const char *nome_pdf) {
    char comando_mover[512];
    snprintf(comando_mover, sizeof(comando_mover), "move \".\\%s\\%s\" \".\\e_tickets\\\"", pasta, nome_pdf);
    system(comando_mover);

    char comando_remover[512];
    snprintf(comando_remover, sizeof(comando_remover), "rmdir /s /q %s", pasta);
    system(comando_remover);
}

void executarLaTeX (Voo voo, int dia, int mes, int ano, Passageiro passageiro_atual, Pagamento pagamento_atual, char *codigoPortao, int codigoEticket) {
    const char *pasta = "build_latex";
    char nomeArquivoBase[256];
    char arquivo_tex[256];
    char arquivo_pdf[256];
    sprintf (nomeArquivoBase, "%04d_%02d_%02d_%d_%d", ano, mes, dia, voo.codigoRota, codigoEticket);
    sprintf (arquivo_tex, "%s.tex", nomeArquivoBase);
    sprintf (arquivo_pdf, "%s.pdf", nomeArquivoBase);

    // Criar diretório
    if (_mkdir(pasta) == -1) {
        perror("Erro ao criar o diretório");
        exit(1);
    }

    // Gerar o arquivo LaTeX
    gerar_arquivo_latex(voo, dia, mes, ano, passageiro_atual, pagamento_atual, codigoPortao, codigoEticket, pasta, arquivo_tex);

    // Compilar o LaTeX
    compilar_latex(pasta, arquivo_tex);

    // Limpar o diretório temporário
    limpar_diretorio(pasta, arquivo_pdf);

    printf("PDF gerado com sucesso!\n");
}
