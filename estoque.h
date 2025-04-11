#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxprodutos 100
#define nomeArquivo "estoque.csv" 


struct Produto {
    int cod;
    char nome[50];
    char categoria[20];
    int quantidade;
    float preco;
    char data_registro[11]; 
    int porPeso; 
};

struct ProdutoVendido {
    int cod;
    char nome[50];
    int quantidade;
    float preco;
};

void addProduto(struct Produto estoque[], int *contador);
void listarProdutos(struct Produto estoque[], int contador);
void atualizarQuantidade(struct Produto estoque[], int contador);
void removerProduto(struct Produto estoque[], int *contador);
void salvarEstoque(struct Produto estoque[], int contador);
void carregarEstoque(struct Produto estoque[], int *contador);
float ValorTtl(struct Produto p);
void DataAtual(char *data);
void limparTela(); 
void FechamentoCaixa(struct Produto estoque[], int contador, struct ProdutoVendido vendidos[], int contVendas,
                     float saldoDebito, float saldoCredito, float saldoVoucher, float saldoPix, float saldoDinheiro,
                     struct Produto doados[], int contDoacoes);

int TempoRegistro(const char *dataRegistro, const char *dataAtual);

void PrdtsDoacao(struct Produto estoque[], int *contador, struct Produto doados[], int *contDoacoes);

#endif
