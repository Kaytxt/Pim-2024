#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estoque.h"
#include <locale.h>



void rgstrVenda(struct Produto estoque[], int *contador, struct ProdutoVendido vendidos[], int *contVendas,
                float *saldoDebito, float *saldoCredito, float *saldoVoucher, float *saldoPix, float *saldoDinheiro);
void FechamentoCaixa(struct Produto estoque[], int contador, struct ProdutoVendido vendidos[], int contVendas,
                     float saldoDebito, float saldoCredito, float saldoVoucher, float saldoPix, float saldoDinheiro,
                     struct Produto doados[], int contDoacoes);

int main() {
    struct Produto estoque[maxprodutos];
    struct ProdutoVendido vendidos[100];
    struct Produto doados[100]; 
    int contador = 0, contVendas = 0, contDoacoes = 0, opcao;

    carregarEstoque(estoque, &contador);

    float saldoDebito = 0.0, saldoCredito = 0.0, saldoVoucher = 0.0, saldoPix = 0.0, saldoDinheiro = 0.0;

    do {
        printf("\n========================================\n");
        printf("  SISTEMA DE ESTOQUE E VENDAS\n");
        printf("========================================\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Registrar Venda\n");
        printf("4. Verificar Doações\n");
        printf("5. Salvar Estoque\n");
        printf("6. Fechamento de Caixa\n");
        printf("7. Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                addProduto(estoque, &contador);
                break;
            case 2:
                listarProdutos(estoque, contador);
                break;
            case 3:
                rgstrVenda(estoque, &contador, vendidos, &contVendas, &saldoDebito, &saldoCredito, &saldoVoucher, &saldoPix, &saldoDinheiro);
                break;
            case 4:
                PrdtsDoacao(estoque, &contador, doados, &contDoacoes);
                break;
            case 5:
                salvarEstoque(estoque, contador);
                break;
            case 6:
                FechamentoCaixa(estoque, contador, vendidos, contVendas, saldoDebito, saldoCredito, saldoVoucher, saldoPix, saldoDinheiro, doados, contDoacoes);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}

void rgstrVenda(struct Produto estoque[], int *contador, struct ProdutoVendido vendidos[], int *contVendas,
                float *saldoDebito, float *saldoCredito, float *saldoVoucher, float *saldoPix, float *saldoDinheiro) {
    int continuarCompra = 1;

    while (continuarCompra == 1) {
        int cod, quantidade;
        printf("\nDigite o código do produto: ");
        scanf("%d", &cod);

        struct Produto *produto = NULL;
        int i;
        for (i = 0; i < *contador; i++) {
            if (estoque[i].cod == cod) {
                produto = &estoque[i];
                break;
            }
        }

        if (produto == NULL) {
            printf("Produto não encontrado no estoque.\n");
            return;
        }

        printf("Digite a quantidade a ser vendida: ");
        scanf("%d", &quantidade);

        while (quantidade > produto->quantidade) {
            printf("Quantidade insuficiente no estoque. Tente novamente.\n");
            printf("Digite a quantidade a ser vendida: ");
            scanf("%d", &quantidade);
        }

        produto->quantidade -= quantidade;

        vendidos[*contVendas].cod = produto->cod;
        strcpy(vendidos[*contVendas].nome, produto->nome);
        vendidos[*contVendas].quantidade = quantidade;
        vendidos[*contVendas].preco = produto->preco;
        (*contVendas)++;

        printf("Deseja continuar comprando outros produtos? (1 - Sim / 0 - Não): ");
        scanf("%d", &continuarCompra);
    }

    int formaPagamento;
    printf("\nEscolha a forma de pagamento (1 a 5):\n");
    printf("1 - Débito\n");
    printf("2 - Crédito\n");
    printf("3 - Voucher\n");
    printf("4 - Pix\n");
    printf("5 - Dinheiro\n");
    scanf("%d", &formaPagamento);

    float ValorTotal = 0;
    int i;
    for (i = 0; i < *contVendas; i++) {
        ValorTotal += vendidos[i].preco * vendidos[i].quantidade;
    }

    switch (formaPagamento) {
        case 1:
            *saldoDebito += ValorTotal;
            break;
        case 2:
            *saldoCredito += ValorTotal;
            break;
        case 3:
            *saldoVoucher += ValorTotal;
            break;
        case 4:
            *saldoPix += ValorTotal;
            break;
        case 5:
            *saldoDinheiro += ValorTotal;
            break;
        default:
            printf("Opção de pagamento inválida.\n");
            return;
    }

    printf("\nVenda registrada com sucesso!\n");
}

void PrdtsDoacao(struct Produto estoque[], int *contador, struct Produto doados[], int *contDoacoes) {
    char dataAtual[11];
    DataAtual(dataAtual);

    printf("\nProdutos com mais de 3 dias no estoque:\n");
    int i;
    for (i = 0; i < *contador; i++) {
        int dias = TempoRegistro(estoque[i].data_registro, dataAtual);
        if (dias > 3) {
            printf("Produto: %s (Código: %d) - Quantidade: %d\n", estoque[i].nome, estoque[i].cod, estoque[i].quantidade);
        }
    }

    int cod, quantidade, doar;
    printf("\nDeseja doar algum produto? (1 - Sim / 0 - Não): ");
    scanf("%d", &doar);

    if (doar == 1) {
        printf("Digite o código do produto a ser doado: ");
        scanf("%d", &cod);

        struct Produto *produto = NULL;
        for (i = 0; i < *contador; i++) {
            if (estoque[i].cod == cod) {
                produto = &estoque[i];
                break;
            }
        }

        if (produto == NULL) {
            printf("Produto não encontrado no estoque.\n");
            return;
        }

        printf("Digite a quantidade a ser doada: ");
        scanf("%d", &quantidade);

        while (quantidade > produto->quantidade) {
            printf("Quantidade insuficiente no estoque. Tente novamente.\n");
            printf("Digite a quantidade a ser doada: ");
            scanf("%d", &quantidade);
        }

        produto->quantidade -= quantidade;

        doados[*contDoacoes].cod = produto->cod;
        strcpy(doados[*contDoacoes].nome, produto->nome);
        doados[*contDoacoes].quantidade = quantidade;
        (*contDoacoes)++;

        printf("Doação registrada com sucesso!\n");
    }
}

void FechamentoCaixa(struct Produto estoque[], int contador, struct ProdutoVendido vendidos[], int contVendas,
                     float saldoDebito, float saldoCredito, float saldoVoucher, float saldoPix, float saldoDinheiro,
                     struct Produto doados[], int contDoacoes) {
    FILE *fechamento = fopen("fechamento_caixa.txt", "a");
    if (fechamento == NULL) {
        printf("Erro ao abrir o arquivo de fechamento de caixa.\n");
        return;
    }

    fprintf(fechamento, "======================== FECHAMENTO DE CAIXA ========================\n");
    fprintf(fechamento, "Data: %s\n", __DATE__);
    fprintf(fechamento, "-----------------------------------------------------------\n");
    fprintf(fechamento, "Vendas por forma de pagamento:\n");
    fprintf(fechamento, "Débito: %.2f\n", saldoDebito);
    fprintf(fechamento, "Crédito: %.2f\n", saldoCredito);
    fprintf(fechamento, "Voucher: %.2f\n", saldoVoucher);
    fprintf(fechamento, "Pix: %.2f\n", saldoPix);
    fprintf(fechamento, "Dinheiro: %.2f\n", saldoDinheiro);

    fprintf(fechamento, "-----------------------------------------------------------\n");
    fprintf(fechamento, "Produtos Vendidos:\n");
    int i;
    for (i = 0; i < contVendas; i++) {
        fprintf(fechamento, "Produto: %s (Código: %d) - Quantidade: %d - Valor Unitário: %.2f\n",
                vendidos[i].nome, vendidos[i].cod, vendidos[i].quantidade, vendidos[i].preco);
    }

    fprintf(fechamento, "-----------------------------------------------------------\n");
    fprintf(fechamento, "Produtos Doados:\n");

    for (i = 0; i < contDoacoes; i++) {
        fprintf(fechamento, "Produto: %s (Código: %d) - Quantidade: %d\n", doados[i].nome, doados[i].cod, doados[i].quantidade);
    }

    fprintf(fechamento, "====================================================================\n");
    fclose(fechamento);
    printf("Fechamento de caixa registrado com sucesso!\n");
}
