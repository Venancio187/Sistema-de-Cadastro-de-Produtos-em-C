#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;

void adicionarProduto() {
    FILE *arquivo = fopen("produtos.txt", "a");
    Produto p;

    printf("Codigo: ");
    scanf("%d", &p.codigo);
    printf("Nome: ");
    scanf(" %[^\n]", p.nome);
    printf("Preco: ");
    scanf("%f", &p.preco);

    fprintf(arquivo, "%d;%s;%.2f\n", p.codigo, p.nome, p.preco);
    fclose(arquivo);

    printf("Produto adicionado com sucesso!\n");
}

void listarProdutos() {
    FILE *arquivo = fopen("produtos.txt", "r");
    Produto p;

    printf("\nLista de Produtos:\n");
    while (fscanf(arquivo, "%d;%49[^;];%f\n", &p.codigo, p.nome, &p.preco) != EOF) {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2f\n", p.codigo, p.nome, p.preco);
    }
    fclose(arquivo);
}

void buscarProduto() {
    FILE *arquivo = fopen("produtos.txt", "r");
    Produto p;
    int codigo, encontrado = 0;

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d;%49[^;];%f\n", &p.codigo, p.nome, &p.preco) != EOF) {
        if (p.codigo == codigo) {
            printf("Produto encontrado: %s - R$ %.2f\n", p.nome, p.preco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("Produto nao encontrado.\n");

    fclose(arquivo);
}

void excluirProduto() {
    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Produto p;
    int codigo, encontrado = 0;

    printf("Digite o codigo do produto a excluir: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d;%49[^;];%f\n", &p.codigo, p.nome, &p.preco) != EOF) {
        if (p.codigo != codigo) {
            fprintf(temp, "%d;%s;%.2f\n", p.codigo, p.nome, p.preco);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");

    if (encontrado)
        printf("Produto excluido com sucesso!\n");
    else
        printf("Produto nao encontrado.\n");
}

int main() {
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto\n");
        printf("4. Excluir Produto\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: buscarProduto(); break;
            case 4: excluirProduto(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}



