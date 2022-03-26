#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  --- estruturas ---  //
typedef struct Pessoa {
    int documento;
    char descricao[26];
    char vacina[13];
    struct Pessoa *prox;
} Pessoa;

typedef struct Pessoa *p_pessoa;


//  --- funções ---  //

/* Retorna "NULL" para inicializar uma lista. */
p_pessoa criarLista(){

    return NULL;
}

/* Realiza a liberação de memória para a lista fornecida. */
void destruirLista(p_pessoa lista){
    if (lista != NULL){
        destruirLista(lista->prox);
        free(lista);
    }
}

/* Cria e inicializa um elemento com os parâmetros fornecidos. */
p_pessoa criarElemento(int documento, char descricao[26], char vacina[13]){
    p_pessoa novo;
    novo = malloc(sizeof(Pessoa));
    novo->documento = documento;
    strcpy(novo->descricao, descricao);
    strcpy(novo->vacina, vacina);
    novo->prox = NULL;
    return novo;
}

/* Adiciona o elemento fornecido ao início da lista inserida. */
p_pessoa adicionarNoComeco(p_pessoa lista, p_pessoa elemento){
    elemento->prox = lista;
    return elemento;
}

/* Adiciona o elemento fornecido ao final da lista inserida. */
p_pessoa adicionarPorUltimo(p_pessoa lista, p_pessoa elemento){
    if (lista == NULL){
        return elemento;
    }
    lista->prox = adicionarPorUltimo(lista->prox, elemento);
    return lista;
}

/* Adiciona um elemento em uma lista após um outro elemento anterior fornecido. */
void adicionarEspecifico(p_pessoa anterior, p_pessoa elemento){
    elemento->prox = anterior->prox;
    anterior->prox = elemento;
}

/* Imprime todos os elementos da lista fornecida recursivamente. */
void imprimirLista(p_pessoa lista){
    if (lista != NULL){
        printf("%i %s %s\n", lista->documento, lista->descricao, lista->vacina);
        imprimirLista(lista->prox);
    }
}


//  --- programa principal ---  //

int main(){
    // inicialização das variáveis e leitura dos dados
    int documento;
    char descricao[26], vacina[13];
    p_pessoa fila, lanterna, pessoa;

    fila = criarLista();

    while(scanf("%i ", &documento) != EOF){
        scanf("%s ", descricao);
        scanf("%s ", vacina);

        // criação de um novo elemento com os dados obtidos
        pessoa = criarElemento(documento, descricao, vacina);

        // condições para adição na fila a partir de cada descrição
        if(!strcmp(descricao, "coach") || !strcmp(descricao, "ex-bbb") || !strcmp(descricao, "filho-politico") || !strcmp(descricao, "herdeiro") || !strcmp(descricao, "youtuber-financas")){
            fila = adicionarNoComeco(fila, pessoa);
            lanterna = pessoa;

        } else if (!strcmp(descricao, "funcionario")){ // se for um funcionário
            fila = adicionarPorUltimo(fila, pessoa);
            lanterna = pessoa;

        } else if (!strcmp(descricao, "fiscal")){ // se for um fiscal
            if (fila == NULL){
                fila = adicionarNoComeco(fila, pessoa);
                lanterna = fila;

            } else if(!strcmp(lanterna->descricao, "fiscal") && !strcmp(pessoa->vacina, "nao-vacinado")){
                free(pessoa);
            
            } else { 
                adicionarEspecifico(lanterna, pessoa);
                lanterna = pessoa;
                while(pessoa->prox != NULL && strcmp(pessoa->prox->vacina, "vacinado")){
                    p_pessoa aux = malloc(sizeof(Pessoa));
                    aux = pessoa->prox->prox;
                    free(pessoa->prox);
                    pessoa->prox = aux;
                }
            }

        } else { // se for uma pessoa normal
            if (fila == NULL){
                fila = adicionarNoComeco(fila, pessoa);
                lanterna = fila;

            } else if (!strcmp(lanterna->descricao, "fiscal") && !strcmp(pessoa->vacina, "nao-vacinado")){
                free(pessoa);

            } else {
                adicionarEspecifico(lanterna, pessoa);
                lanterna = pessoa;
            }
        }
    }

    // impressão e liberação da memória
    imprimirLista(fila);
    destruirLista(fila);

    return 0;
}