#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Loja{
    char nome[15];
    double valor;
    struct Loja *esq, *dir;
} Loja;
typedef Loja *p_loja;

p_loja criarArvoreLojas(char nome[15], double valor, p_loja esq, p_loja dir){
    /* cria e retorna uma nova árvore binária com os parâmetros fornecidos */
    p_loja raiz = malloc(sizeof(Loja));
    strcpy(raiz->nome, nome);
    raiz->valor = valor;
    raiz->esq = esq;
    raiz->dir = dir;
    return raiz;
}

p_loja inserirLoja(p_loja raiz, char nome[15], float valor){
    /* adiciona uma loja à árvore binária de busca cuja raiz é fornecida de forma */
    p_loja novo;
    if(raiz == NULL){
        novo = malloc(sizeof(Loja));
        novo->esq = novo->dir = NULL;
        strcpy(novo->nome, nome);
        novo->valor = valor;
        return novo;
    }
    if(strcmp(nome, raiz->nome) < 0){
        raiz->esq = inserirLoja(raiz->esq, nome, valor);
    } else {
        raiz->dir = inserirLoja(raiz->dir, nome, valor);
    }
    return raiz;
}

typedef struct Produto{
    int codigo;
    p_loja lojas;
    struct Produto *esq, *dir;
} Produto;
typedef Produto *p_produto;

p_produto criarArvoreProdutos(int codigo, char nome[15], double valor, p_produto esq, p_produto dir){
    /* cria e retorna uma nova árvore binária com os parâmetros fornecidos */
    p_produto raiz = malloc(sizeof(Produto));
    raiz->codigo = codigo;
    raiz->lojas = criarArvoreLojas(nome, valor, NULL, NULL);
    raiz->esq = esq;
    raiz->dir = dir;
    return raiz;
}

p_produto inserirProduto(p_produto raiz, int codigo, char nome[15], float valor){
    /* adiciona um produto à árvore binária de busca cuja raiz é fornecida de forma */
    p_produto novo;
    if(raiz == NULL){
        novo = malloc(sizeof(Produto));
        novo->esq = novo->dir = NULL;
        novo->codigo = codigo;
        novo->lojas = criarArvoreLojas(nome, valor, NULL, NULL);
        return novo;
    }
    if(codigo < raiz->codigo){
        raiz->esq = inserirProduto(raiz->esq, codigo, nome, valor);
    } else {
        raiz->dir = inserirProduto(raiz->dir, codigo, nome, valor);
    }
    return raiz;
}

void destruirArvoreLojas(p_loja raiz){
    /* libera a memória de uma árvore cuja raiz é fornecida */
    if(raiz == NULL){
        return;
    }
    destruirArvoreLojas(raiz->esq);
    destruirArvoreLojas(raiz->dir);
    free(raiz);
}

void destruirArvoreProdutos(p_produto raiz){
    /* libera a memória de uma árvore cuja raiz é fornecida */
    if(raiz == NULL){
        return;
    }
    destruirArvoreLojas(raiz->lojas);
    destruirArvoreProdutos(raiz->esq);
    destruirArvoreProdutos(raiz->dir);
    free(raiz);
}

p_produto buscarArvore(p_produto raiz, int codigo){
    /* busca um código específico em uma árvore binária de busca cuja raíz é fornecida */
    if(raiz == NULL){
        return raiz;
    }
    if(codigo == raiz->codigo){
        return raiz;
    }
    if(codigo < raiz->codigo){
        return buscarArvore(raiz->esq, codigo);
    } else {
        return buscarArvore(raiz->dir, codigo);
    }
    return NULL;
}

void imprimirNaSequencia(p_loja raiz, int codigo, float valor, int *imprimiu){
    /* imprime todas as lojas e produtos que cumprem os requisitos de valor */
    if(raiz == NULL){
        return;
    }
    imprimirNaSequencia(raiz->esq, codigo, valor, imprimiu);
    if(raiz->valor <= valor * 1.1){
        printf("%s %i %.2f\n", raiz->nome, codigo, raiz->valor);
        *imprimiu += 1;
    }
    imprimirNaSequencia(raiz->dir, codigo, valor, imprimiu);
}

int main(){
    // inicialização das variáveis
    int n, m, codigo;
    float valor;
    char nome[15];

    // leitura dos dados para cada entrada e inserção nas respectivas árvores
    scanf("%d ", &n);
    p_produto produtos = NULL;
    for(int i=0; i<n; i++){
        scanf("%s %d %f", nome, &codigo, &valor);

        if(produtos == NULL){ // se a árvore for vazia
            produtos = criarArvoreProdutos(codigo, nome, valor, NULL, NULL);
        } else {
            if(buscarArvore(produtos, codigo) == NULL){ // se o produto ainda não estiver na árvore
                produtos = inserirProduto(produtos, codigo, nome, valor);
            } else { // se o produto já estiver na árvore
                p_produto aux;
                aux = buscarArvore(produtos, codigo);
                aux->lojas = inserirLoja(aux->lojas, nome, valor);
            }
        }
    }

    // leitura dos produtos requisitados, busca e impressao das melhores ofertas
    scanf("%d ", &m);
    for(int i=0; i<m; i++){
        scanf("%d %f", &codigo, &valor);

        p_produto aux = NULL;
        aux = buscarArvore(produtos, codigo);

        if(aux != NULL){ // se o código foi encontrado
            int imprimiu = 0; // variável utilizada para fazer a contagem das ofertas encontradas
            printf("OFERTAS para %i:\n", codigo);
            imprimirNaSequencia(aux->lojas, codigo, valor, &imprimiu);
            if(imprimiu == 0){ // caso nenhuma boa oferta tenha sido encontrada
                printf("nenhuma boa oferta foi encontrada\n");
            }
            printf("\n");

        } else {
            printf("OFERTAS para %i:\n", codigo);
            printf("nenhuma boa oferta foi encontrada\n");
        }
    }

    // liberação da memória
    destruirArvoreProdutos(produtos);

    return 0;
}