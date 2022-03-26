#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//  --- estruturas ---  //

typedef struct Palavra{
    char chave[50];
    int vezes;
    struct Palavra *prox;
} Palavra;
typedef Palavra *p_palavra;

typedef struct{
    p_palavra *vetor;
} Hash;
typedef Hash * p_hash;


//  --- funções ---  //

/* Insere uma nova palavra a uma lista ligada fornecida. */
p_palavra inserirLista(p_palavra lista, char *chave){
    p_palavra novo;
    novo = malloc(sizeof(Palavra));
    strcpy(novo->chave, chave);
    novo->vezes = 1;
    novo->prox = lista;
    return novo;
}

/** Busca por uma palavra em uma lista ligada fornecida e 
 * retorna-a, se encontrada, ou retorna NULL em caso contrário. */
p_palavra buscarLista(p_palavra lista, char *chave){
    if(lista == NULL){
        return NULL;
    }
    if(strcmp(lista->chave, chave) == 0){
        return lista;
    }
    return buscarLista(lista->prox, chave);
}

/* Imprime uma lista ligada fornecida. */
void imprimirLista(p_palavra lista){
    if (lista != NULL){
        printf("%s %d\n", lista->chave, lista->vezes);
        imprimirLista(lista->prox);
    }
}

/* Realiza a liberação da memória de uma lista ligada fornecida. */
void destruirLista(p_palavra lista){
    if(lista != NULL){
        destruirLista(lista->prox);
        free(lista);
    }
}

/* Cria um novo hash com um numeró máximo de vetores fornecido. */
p_hash criarHash(int max){
    p_hash t = malloc(sizeof(Hash));
    t->vetor = malloc(max * sizeof(Palavra));
    for(int i=0; i < max; i++){
        t->vetor[i] = NULL;
    }
    return t;
}

/* Calcula a posição de uma palavra no hash com base em sua chave. */
int hash(char *chave, int max){
    int i, nchave=0, n=0;
    for(i=0; i < strlen(chave); i++){
        nchave += chave[i];
        n = (n + chave[i]) % max;
    }
    n = nchave % max;
    return n;
}

/* Insere uma palavra em um hash fornecido. */
void inserirHash(p_hash t, char *chave, int max){
    int n = hash(chave, max);
    t->vetor[n] = inserirLista(t->vetor[n], chave);
}

/** Busca a chave de uma palavra em um hash e a retorna, caso encontrada.
 * Caso a palavra não seja encontrada, retorna NULL. */
p_palavra buscarHash(p_hash t, char *chave, int max){
    int n = hash(chave, max);
    return buscarLista(t->vetor[n], chave);
}

/* Função auxiliar da mergeSort. */
void merge(p_palavra *v, int l, int m, int r){
    p_palavra *aux = malloc(r * sizeof(Palavra));
    int i=l, j=m+1, k=0;
    // intercala
    while(i <= m && j <= r){
        if(v[i]->vezes > v[j]->vezes){
            aux[k++] = v[i++];
        } else if (v[i]->vezes == v[j]->vezes){
            if(strcmp(v[i]->chave, v[j]->chave) < 0){
                aux[k++] = v[i++];
            } else {
                aux[k++] = v[j++];
            }
        } else{
            aux[k++] = v[j++];
        }
    }
    // copia o resto do subvetor que não terminou
    while (i <= m){
        aux[k++] = v[i++];
    }
    while (j <= r){
        aux[k++] = v[j++];
    }
    // copia de volta para v
    for(i=l, k=0; i<=r; i++, k++){
        v[i] = aux[k];
    }
    free(aux);
}

/** Ordena um vetor de palavras com base no número
 *  de vezes em que elas foram encontradas e, para 
 * números iguais de vezes, em ordem alfabética. */
void mergeSort(p_palavra *v, int l, int r) {
    int m = (l + r) / 2;
    if (l < r) {
        // divisão
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        // conquista
        merge(v, l, m, r);
    }
}

/* Realiza a liberação da memória de um hash. */
void destruirHash(p_hash t, int max){
    for(int i=0; i < max; i++){
        destruirLista(t->vetor[i]);
    }
    free(t->vetor);
    free(t);
}


//  --- programa principal ---  //

int main(){
    //leituras iniciais
    int total=0, nStopWords=0;
    scanf("%d ", &total);
    scanf("%d ", &nStopWords);

    // vetor para armazenar as palavras aceitas
    p_palavra *palavrasAceitas = malloc(total * sizeof(Palavra));
    int auxPA = 0; // contador de palavras aceitas

    // leitura e armazenamento das stop words
    p_palavra stopWords = NULL;
    for(int i=0; i<nStopWords; i++){
        char aux[10];
        scanf("%s ", aux);
        stopWords = inserirLista(stopWords, aux);
    }

    // processos para leitura, armazenamento e verificação das palavras
    p_hash hashPalavras = NULL;
    hashPalavras = criarHash(total);

    char entrada[50];
    while(scanf("%s ", entrada) != EOF){

        // verificação dos caracteres
        for(int i=0, j; entrada[i] != '\0'; i++){
            entrada[i] = tolower(entrada[i]);
            while(!isalpha(entrada[i]) && entrada[i] != '\0'){
                for(j=i; entrada[j] != '\0'; j++){
                    entrada[j] = tolower(entrada[j+1]);
                }
                entrada[j] = '\0';
            }
        }

        // verificação de se a palavra já está no hash e armazenamento ou descarte das mesmas
        if(strlen(entrada) > 1){
            p_palavra aux = buscarLista(stopWords, entrada);
            if(aux == NULL){
                aux = buscarHash(hashPalavras, entrada, total);
                if(aux == NULL){ // se ainda não está no hash
                    inserirHash(hashPalavras, entrada, total);
                    // cópia da palavra inserida para o vetor de palavras aceitas
                    palavrasAceitas[auxPA] = buscarHash(hashPalavras, entrada, total);
                    auxPA++;
                } else { // se já está no hash
                    aux->vezes++;
                }
            }
        }
    }

    // ordenação do vetor de palavras aceitas e impressão
    mergeSort(palavrasAceitas, 0, auxPA-1);
    for(int i=0; i < auxPA && i < 50; i++){
        printf("%s %d\n", palavrasAceitas[i]->chave, palavrasAceitas[i]->vezes);
    }

    // liberação da memória
    destruirHash(hashPalavras, total);
    destruirLista(stopWords);
    free(palavrasAceitas);

    return 0;
}