#include "estoque.h"



void limparTela() {
    #ifdef _WIN32
        system("cls");  
    #endif
}

void addProduto(struct Produto estoque[], int *contador) {
    int cod, categoriaOpcao, i;
    struct Produto *produtoExistente = NULL;

    printf("\n=======================================\n");
    printf("      Adicionar Produto ao Estoque\n");
    printf("=======================================\n");

    printf("Digite o código do produto: ");
    scanf("%d", &cod);

    for (i = 0; i < *contador; i++) {
        if (estoque[i].cod == cod) {
            produtoExistente = &estoque[i];
            break;
        }
    }

    if (produtoExistente != NULL) {
        int quantidadeAdicionar;
        printf("Produto já existe. Digite a quantidade para adicionar: ");
        scanf("%d", &quantidadeAdicionar);

        produtoExistente->quantidade += quantidadeAdicionar;
        printf("Quantidade incrementada com sucesso!\n");
    } else {
        if (*contador >= maxprodutos) {
            printf("Estoque completamente cheio!\n");
            return;
        }

        struct Produto novoProduto;
        novoProduto.cod = cod;

        while (1) {
            printf("Escolha a categoria do produto:\n");
            printf("1 - Fruta\n");
            printf("2 - Verdura\n");
            printf("3 - Legume\n");
            printf("4 - Orgânico\n");
            printf("Digite a opção: ");
            scanf("%d", &categoriaOpcao);

            if (categoriaOpcao >= 1 && categoriaOpcao <= 4) {
                switch (categoriaOpcao) {
                    case 1: strcpy(novoProduto.categoria, "Fruta"); break;
                    case 2: strcpy(novoProduto.categoria, "Verdura"); break;
                    case 3: strcpy(novoProduto.categoria, "Legume"); break;
                    case 4: strcpy(novoProduto.categoria, "Orgânico"); break;
                }
                break;
            } else {
                printf("Opção inválida. Tente novamente.\n");
            }
        }

        printf("Digite o nome do produto: ");
        scanf(" %[^\n]", novoProduto.nome);

        printf("O produto será vendido por:\n1 - Quilograma\n2 - Unidade\n");
        int escolhaVenda;
        scanf("%d", &escolhaVenda);
        if (escolhaVenda == 1) {
            novoProduto.porPeso = 1;
            printf("Digite a quantidade em Kg do produto: ");
        } else if (escolhaVenda == 2) {
            novoProduto.porPeso = 0;
            printf("Digite a quantidade de unidades do produto: ");
        } else {
            printf("Opção inválida! Produto não adicionado.\n");
            return;
        }

        scanf("%d", &novoProduto.quantidade);

        printf("Digite o preço unitário do produto: ");
        scanf("%f", &novoProduto.preco);

        DataAtual(novoProduto.data_registro);

        estoque[*contador] = novoProduto;
        (*contador)++;

        printf("Produto adicionado com sucesso!\n");
        limparTela();
    }
}

void listarProdutos(struct Produto estoque[], int contador) {
    if (contador == 0) {
        printf("\nNenhum produto foi encontrado no estoque.\n");
        return;
    }

    printf("\n=====================================\n");
    printf("        Produtos no Estoque\n");
    printf("=====================================\n");

    int i;
    printf("| %-6s | %-20s | %-10s | %-10s | %-10s | %-15s | %-10s | %-10s |\n", 
           "Código", "Nome", "Categoria", "Quantidade", "Preço", "Data Registro", "Valor Total", "Medida");
    printf("|--------|----------------------|------------|------------|------------|------------------|------------|------------|\n");
    for (i = 0; i < contador; i++) {
        char tipoVenda[10];
        if (estoque[i].porPeso == 1) {
            strcpy(tipoVenda, "Kg");
        } else {
            strcpy(tipoVenda, "Unidade");
        }

        printf("| %-6d | %-20s | %-10s | %-10d | R$%-9.2f | %-15s | R$%-9.2f | %-10s |\n", 
               estoque[i].cod, estoque[i].nome, estoque[i].categoria, estoque[i].quantidade, 
               estoque[i].preco, estoque[i].data_registro, ValorTtl(estoque[i]), tipoVenda);
    }
    printf("=====================================\n");
}

float ValorTtl(struct Produto p) {
    return p.quantidade * p.preco;
}

void salvarEstoque(struct Produto estoque[], int contador) {
    FILE *arquivo = fopen("estoque.csv", "w");  
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "Código,Nome,Categoria,Quantidade,Preço,Data de Registro,Por Peso\n");
    int i;
    for (i = 0; i < contador; i++) {
        fprintf(arquivo, "%d,%s,%s,%d,%.2f,%s,%d\n",
                estoque[i].cod,
                estoque[i].nome,
                estoque[i].categoria,
                estoque[i].quantidade,
                estoque[i].preco,
                estoque[i].data_registro,
                estoque[i].porPeso);
    }

    fclose(arquivo);
    printf("Estoque salvo em formato CSV com sucesso!\n");
}

void carregarEstoque(struct Produto estoque[], int *contador) {
    FILE *arquivo = fopen("estoque.csv", "r");  
    if (arquivo == NULL) {
        printf("Nenhum arquivo de estoque encontrado. Iniciando com estoque vazio.\n");
        return;
    }

    char linha[200];
    fgets(linha, sizeof(linha), arquivo); 

    while (fscanf(arquivo, "%d,%49[^,],%19[^,],%d,%f,%10[^,],%d\n",
                  &estoque[*contador].cod,
                  estoque[*contador].nome,
                  estoque[*contador].categoria,
                  &estoque[*contador].quantidade,
                  &estoque[*contador].preco,
                  estoque[*contador].data_registro,
                  &estoque[*contador].porPeso) != EOF) {
        (*contador)++;
    }

    fclose(arquivo);
    printf("Estoque carregado a partir do CSV com sucesso!\n");
}

void DataAtual(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int TempoRegistro(const char *dataRegistro, const char *dataAtual) {
    struct tm data1 = {0}, data2 = {0};

    sscanf(dataRegistro, "%2d/%2d/%4d", &data1.tm_mday, &data1.tm_mon, &data1.tm_year);
    sscanf(dataAtual, "%2d/%2d/%4d", &data2.tm_mday, &data2.tm_mon, &data2.tm_year);

    data1.tm_mon -= 1;
    data1.tm_year -= 1900;
    data2.tm_mon -= 1;
    data2.tm_year -= 1900;

    time_t t1 = mktime(&data1);
    time_t t2 = mktime(&data2);

    double diff = difftime(t2, t1);
    return (int)(diff / (60 * 60 * 24));
}

