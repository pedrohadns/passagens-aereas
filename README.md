# Sistema de Vendas de Passagens Aéreas
Trabalho realizado em grupo utilizando a linguagem C para a disciplina de Programação Estruturada do curso de Engenharia da Computação da Universidade Federal do Espírito Santo - Campus São Mateus

## 📌 Funcionalidades  

- Seleção de origem e destino entre aeroportos cadastrados.  
- Escolha de horários disponíveis conforme os voos e conexões.  
- Sistema de assentos atualizado a cada venda.  
- Processamento de pagamentos (dinheiro, cartão de crédito/débito).  
- Geração de e-ticket em formato **TXT/PDF**.  
- Armazenamento de dados em arquivos `.dat` para persistência.  

## 🏗 Estrutura do Código  

O projeto segue um design modular, utilizando **funções**, **structs**, **vetores** e **arquivos**. As principais funcionalidades estão divididas em módulos:  

- **Gerenciamento de Aeroportos e Rotas**  
- **Cadastro e Pesquisa de Passageiros**  
- **Seleção e Venda de Passagens**  
- **Pagamentos e Emissão de Bilhetes**  

## 📁 Arquivos  

- `main.c` - Arquivo principal do programa.  
- `aeroportos.c` / `aeroportos.h` - Cadastro e consulta de aeroportos.  
- `voos.c` / `voos.h` - Gerenciamento de voos e assentos.  
- `pagamentos.c` / `pagamentos.h` - Processamento de pagamentos.  
- `eticket.c` / `eticket.h` - Geração de bilhetes eletrônicos.  
- `data/voos.dat` - Banco de dados com voos cadastrados.  
- `data/vendas.dat` - Registro de passagens vendidas.  

## ⚙️ Compilação e Execução  

Para compilar o programa, utilize um compilador **GCC**:  

```bash
gcc main.c aeroportos.c voos.c pagamentos.c eticket.c -o vendas_passagens
```

Para executar:  

```bash
./vendas_passagens
```

## 📜 Algoritmo de Cálculo de Passagens  

O preço da passagem é calculado com base em múltiplos fatores, incluindo:  

- **Distância (milhas)**  
- **Tempo até a viagem**  
- **Dia da semana e feriados**  
- **Taxa de ocupação do voo**  

A fórmula principal para o cálculo é:  

```
Custo Trecho = DIST * MILHA * FATOR_PER * FATOR_DUFFS * FATOR_RET * FATOR_PROC
```

## 🛠 Melhorias Futuras  

- Implementação de interface gráfica.

## 📄 Licença  

Este projeto está licenciado sob a **Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)**.  

Você pode:  
- **Compartilhar** – copiar e redistribuir o material em qualquer meio ou formato.  
- **Adaptar** – remixar, transformar e criar a partir do material.  

**Mas NÃO pode:**  
- Usar para fins comerciais sem autorização.  

Leia mais sobre a licença em: [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/).  
