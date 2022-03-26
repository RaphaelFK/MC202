#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char nome[20];
    double valor;
    struct Pessoa *esq, *dir, *pai;
} Pessoa;
typedef Pessoa *p_pessoa;

p_pessoa criarArvore(char nome[20], double valor, p_pessoa esq, p_pessoa dir, p_pessoa pai){
    /* cria e retorna uma nova árvore binária com os parâmetros fornecidos */
    p_pessoa raiz = malloc(sizeof(Pessoa));
    strcpy(raiz->nome, nome);
    raiz->valor = valor;
    raiz->esq = esq;
    raiz->dir = dir;
    raiz->pai = pai;
    return raiz;
}

void destruirArvore(p_pessoa raiz){
    /* libera a memória de uma árvore cuja raiz é fornecida */
    if(raiz == NULL){
        return;
    }
    destruirArvore(raiz->esq);
    destruirArvore(raiz->dir);
    free(raiz);
}

p_pessoa procurarPessoa(p_pessoa raiz, char nome[20]){
    /* 
    procura em uma árvore determinada e retorna o ponteiro de uma pessoa cujo nome é fornecido. 
    caso nenhuma pessoa seja encontrada, retorna "NULL".
    */
    p_pessoa esq;
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0){
        return raiz;
    }
    esq = procurarPessoa(raiz->esq, nome);
    if (esq != NULL){
        return esq;
    }
    return procurarPessoa(raiz->dir, nome);
}

int altura(p_pessoa raiz){
    /* calcula a altura de uma árvore cuja raiz é fornecida */
    int h_esq, h_dir;
    if (raiz == NULL){
        return 0;
    }
    h_esq = altura(raiz->esq);
    h_dir = altura(raiz->dir);
    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

void imprimirNivel(p_pessoa raiz, int nivel){
    /* imprime todos os nós de um nível de uma árvore cuja raiz é fornecida */
    if(raiz == NULL){
        return;
    }
    if (nivel == 1){
        printf(" [%s %.2f]", raiz->nome, raiz->valor);
    } else if (nivel>1){
        imprimirNivel(raiz->esq, nivel-1);
        imprimirNivel(raiz->dir, nivel-1);
    }
}

void imprimirEmOrdem(p_pessoa raiz){
    int alt = altura(raiz);
    for(int i=1; i<=alt; i++){
        printf("Nivel %i:", i);
        imprimirNivel(raiz, i);
        printf("\n");
    }
}

int main(){
    // inicialização das variáveis
    char nome[20], nomeRecrutador[20];
    double valor;

    // criação da árvore que representa o esquema de pirâmide
    scanf("Topo ");
    scanf("%s %lf", nome, &valor);
    p_pessoa piramide = criarArvore(nome, valor, NULL, NULL, NULL);

    // primeira impressão
    printf("Nivel 1: [%s %.2f]\n\n", piramide->nome, piramide->valor);

    while(scanf("%s recruta %s %lf ", nomeRecrutador, nome, &valor) != EOF){
        // encontrar o ponteiro do recrutador
        p_pessoa recrutador;
        recrutador = procurarPessoa(piramide, nomeRecrutador);

        // criação de uma nova pessoa com as informações obtidas e conectá-la ao seu recrutador
        p_pessoa novo = criarArvore(nome, valor, NULL, NULL, recrutador);

        recrutador->valor -= novo->valor * 0.1;
        novo->valor += novo->valor * 0.1;

        if (recrutador->esq == NULL){
            recrutador->esq = novo;
        } else {
            recrutador->dir = novo;

            // remunerações para quando o recrutador recruta as duas pessoas
            p_pessoa ant; int contador=6;
            for(ant=novo; ant->pai != NULL && contador > 0; ant=ant->pai){
                if(contador == 6){ // pagamentos que os dois novos recrutados pagam para o recrutador
                    double vEsq = ant->pai->esq->valor * 0.01 * contador;
                    double vDir = ant->pai->dir->valor * 0.01 * contador;
                    ant->pai->esq->valor -= vEsq;
                    ant->pai->dir->valor -= vDir;
                    ant->pai->valor += vEsq + vDir;
                    contador -= 1;

                } else { // pagamentos aos outros níveis da pirâmide
                    if(ant == ant->pai->dir){ // ver se o recrutado está à direita do recrutador
                        double vDir = ant->pai->dir->valor * 0.01 * contador;
                        ant->pai->dir->valor -= vDir;
                        ant->pai->valor += vDir;

                    } else { // quando o recrutado está à esquerda do recrutador
                        double vEsq = ant->pai->esq->valor * 0.01 * contador;
                        ant->pai->esq->valor -= vEsq;
                        ant->pai->valor += vEsq;
                    }
                    contador -= 1;
                }
            }
        }
        // impressões
        imprimirEmOrdem(piramide);
        printf("\n");
    }
    // liberação da memória
    destruirArvore(piramide);

    return 0;
}