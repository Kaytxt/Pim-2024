
# Sistema de Controle de Estoque e Vendas (PIM 2024) 📦

Este projeto é um sistema desenvolvido em linguagem **C** para gerenciamento de estoque, registro de vendas e controle de caixa. Ele foi criado como parte do Projeto Integrado Multidisciplinar (PIM) de 2024.

O sistema permite cadastrar produtos (frutas, verduras, legumes, orgânicos), realizar vendas com diversas formas de pagamento, gerenciar doações de produtos antigos e gerar relatórios de fechamento de caixa.

## 🚀 Funcionalidades Principais

### 1. Gestão de Estoque
- **Adicionar Produto:** Cadastro de novos itens com Código, Nome, Categoria, Quantidade, Preço e Tipo de Venda (Kg ou Unidade).
- **Listar Produtos:** Visualização de todo o estoque em formato de tabela, mostrando valor total por item.
- **Persistência de Dados:** O estoque é salvo e carregado automaticamente de um arquivo `estoque.csv`.

### 2. Vendas e Caixa
- **Registrar Venda:** Baixa automática no estoque ao vender produtos.
- **Carrinho de Compras:** Permite adicionar múltiplos itens em uma única venda.
- **Múltiplos Pagamentos:** Suporte para Débito, Crédito, Voucher, Pix e Dinheiro.
- **Fechamento de Caixa:** Gera um relatório (`fechamento_caixa.txt`) detalhando o total vendido por cada método de pagamento e a lista de produtos vendidos.

### 3. Controle de Validade/Doações
- **Verificar Doações:** Identifica produtos que estão no estoque há mais de 3 dias (baseado na data de registro) e sugere a doação para evitar desperdício.

## 📂 Estrutura do Projeto

* `main.c`: Contém o menu principal, lógica de vendas e o fluxo do programa.
* `estoque.c`: Implementação das funções de manipulação de dados (adicionar, listar, salvar, carregar, fechar caixa).
* `estoque.h`: Cabeçalho com definições das estruturas (`struct Produto`, `struct ProdutoVendido`) e protótipos das funções.
* `estoque.csv`: Arquivo gerado automaticamente para armazenar os dados do estoque.
* `fechamento_caixa.txt`: Relatório gerado ao realizar o fechamento do caixa.

## 🛠️ Compilação e Execução

Para rodar o projeto, você precisa de um compilador C (como GCC).

1. **Compile os arquivos:**
   bash
   gcc main.c estoque.c -o sistema_estoque

```

2. **Execute o programa:**
* **Windows:**
bash
sistema_estoque.exe

```


* **Linux/Mac:**
```bash
./sistema_estoque

```



## 📝 Uso do Sistema

Ao iniciar, o sistema carregará os dados existentes. O menu principal oferece as seguintes opções:

1. **Adicionar Produto:** Insira os dados do produto. Se o código já existir, a quantidade será somada.
2. **Listar Produtos:** Veja a tabela de itens.
3. **Registrar Venda:** Informe o código e quantidade. Ao final, escolha a forma de pagamento.
4. **Verificar Doações:** Liste itens "antigos" (registrados há > 3 dias) e realize a baixa por doação.
5. **Salvar Estoque:** Grava as alterações no arquivo CSV (o sistema também salva/carrega automaticamente em alguns pontos).
6. **Fechamento de Caixa:** Finaliza o dia, gerando o relatório financeiro e de doações.

---
