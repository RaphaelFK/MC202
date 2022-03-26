#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  --- estruturas ---  //

typedef struct Rpg{
    char nome[35];
    int f, d, co, i, s, ca, n;
    int aceito;
    struct Rpg *prox;
} Rpg;
typedef Rpg *p_rpg;

typedef struct{
    int **adj;
    int n;
} Grafo;
typedef Grafo *p_grafo;


//  --- funções ---  //

/* Cria um novo grafo de tamanho n x n e realiza a sua alocação dinâmica. */
p_grafo criarGrafo(int n){
    p_grafo novo = malloc(sizeof(Grafo));
    novo->n = n;
    novo->adj = malloc(n * sizeof(int *));
    for(int i=0 ; i < n; i++){
        novo->adj[i] = malloc(n * sizeof(int));
    }
    for(int i=0 ; i < n; i++){
        for(int j=0; j < n; j++){
            novo->adj[i][j] = 0;
        }
    }
    return novo;
}

/* Realiza a liberação da memória de um grafo fornecido. */
void destruirGrafo(p_grafo grafo){
    for(int i=0; i < grafo->n; i++){
        free(grafo->adj[i]);
    }
    free(grafo->adj);
    free(grafo);
}

/* Insere uma aresta a-b em um grafo fornecido. */
void inserirAresta(p_grafo grafo, int a, int b){
    grafo->adj[a][b] = 1;
}

/* Verifica se existe uma aresta entre dois vértices fornecidos de um grafo. */
int temAresta(p_grafo grafo, int a, int b){
    return grafo->adj[a][b];
}

/** Procura por um elemento forecido em um vetor específico e retorna o seu índice.
 * Caso o elemento não seja encontrado, retorna -1.
*/
int buscarVetor(p_rpg vetor, int tamanho, int numero){
    for(int x=0; x < tamanho; x++){
        if(vetor[x].n == numero){
            return x;
        }
    }
    return -1;
}

/* Remove um elemento de índice fornecido de um vetor. */
void removerVetor(p_rpg vetor, int indice, int tamanho){
    for(int x=indice; x < tamanho-1; x++){
        vetor[x] = vetor[x+1];
    }
}

/* Preenche um vetor com os parâmetros do jogo de rpg fornecidos. */
void preencheVetor(p_rpg v, int x, char nome[35], int f, int d, int co, int i, int s, int ca){
    strcpy(v[x].nome, nome);
    v[x].f = f; v[x].d = d; v[x].co = co;
    v[x].i = i; v[x].s = s; v[x].ca = ca;
    v[x].n = x; v[x].prox = NULL; 
}


//  --- programa principal ---  //

int main(){
    int nCelas, auxCelas, nNomes, f, d, co, i, s, ca, primeiraCela, segundaCela;
    char nome[35];

    // preenchimento e armazenamento das celas
    scanf("%d ", &nCelas);
    p_rpg celas = malloc(nCelas * sizeof(Rpg)); // vetor com todas as celas
    p_rpg copiaCelas = malloc(nCelas * sizeof(Rpg)); // vetor para remoção das celas não acecíveis
    for(int x=0; x < nCelas; x++){
        scanf("%s %d %d %d %d %d %d ", nome, &f, &d, &co, &i, &s, &ca);
        preencheVetor(celas, x, nome, f, d, co, i, s, ca);
        preencheVetor(copiaCelas, x, nome, f, d, co, i, s, ca);
    }
    
    // preenchimento e armazenamento dos personagens
    scanf("%d ", &nNomes);
    p_rpg personagens = malloc(nNomes * sizeof(Rpg));
    for(int x=0; x < nNomes; x++){
        scanf("%s %d %d %d %d %d %d ", nome, &f, &d, &co, &i, &s, &ca);
        preencheVetor(personagens, x, nome, f, d, co, i, s, ca);
        // numeração das primeiras celas dos personagens
        for(int y=0; y < nCelas; y++){
            if(celas[y].f == f && celas[y].d == d && celas[y].co == co && celas[y].i == i && celas[y].s == s && celas[y].ca == ca){
                personagens[x].n = y;
            }
        }
    }

    auxCelas = nCelas; // auxCelas vai ser utilizado para contar o número de celas do vetor copiaCelas

    for(int x=0; x < nNomes; x++){ // para cada um dos personagens
        p_grafo grafoPersonagem = criarGrafo(nCelas+1); // criação do grafo do personagem
        primeiraCela = personagens[x].n;

        for(int y=0; y < nCelas; y++){
            if(celas[y].n == primeiraCela){
                NULL;
            } else if(celas[primeiraCela].f >= celas[y].f-1 && celas[primeiraCela].d >= celas[y].d && celas[primeiraCela].co >= celas[y].co && celas[primeiraCela].i >= celas[y].i && celas[primeiraCela].s >= celas[y].s && celas[primeiraCela].ca >= celas[y].ca){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);

            } else if(celas[primeiraCela].f >= celas[y].f && celas[primeiraCela].d >= celas[y].d-1 && celas[primeiraCela].co >= celas[y].co && celas[primeiraCela].i >= celas[y].i && celas[primeiraCela].s >= celas[y].s && celas[primeiraCela].ca >= celas[y].ca){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);

            } else if(celas[primeiraCela].f >= celas[y].f && celas[primeiraCela].d >= celas[y].d && celas[primeiraCela].co >= celas[y].co-1 && celas[primeiraCela].i >= celas[y].i && celas[primeiraCela].s >= celas[y].s && celas[primeiraCela].ca >= celas[y].ca){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);

            } else if(celas[primeiraCela].f >= celas[y].f && celas[primeiraCela].d >= celas[y].d && celas[primeiraCela].co >= celas[y].co && celas[primeiraCela].i >= celas[y].i-1 && celas[primeiraCela].s >= celas[y].s && celas[primeiraCela].ca >= celas[y].ca){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);

            } else if(celas[primeiraCela].f >= celas[y].f && celas[primeiraCela].d >= celas[y].d && celas[primeiraCela].co >= celas[y].co && celas[primeiraCela].i >= celas[y].i && celas[primeiraCela].s >= celas[y].s-1 && celas[primeiraCela].ca >= celas[y].ca){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);

            } else if(celas[primeiraCela].f >= celas[y].f && celas[primeiraCela].d >= celas[y].d && celas[primeiraCela].co >= celas[y].co && celas[primeiraCela].i >= celas[y].i && celas[primeiraCela].s >= celas[y].s && celas[primeiraCela].ca >= celas[y].ca-1){
                inserirAresta(grafoPersonagem, primeiraCela, celas[y].n);
            }
        }

        int segundaRodada = nCelas;
        for(int z=0; z < nCelas; z++){
            if(temAresta(grafoPersonagem, primeiraCela, celas[z].n)){
                segundaCela = z;

                for(int y=0; y < nCelas; y++){
                    if(celas[y].n == segundaCela){
                        NULL;
                    } else if(celas[segundaCela].f >= celas[y].f-1 && celas[segundaCela].d >= celas[y].d && celas[segundaCela].co >= celas[y].co && celas[segundaCela].i >= celas[y].i && celas[segundaCela].s >= celas[y].s && celas[segundaCela].ca >= celas[y].ca){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);

                    } else if(celas[segundaCela].f >= celas[y].f && celas[segundaCela].d >= celas[y].d-1 && celas[segundaCela].co >= celas[y].co && celas[segundaCela].i >= celas[y].i && celas[segundaCela].s >= celas[y].s && celas[segundaCela].ca >= celas[y].ca){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);

                    } else if(celas[segundaCela].f >= celas[y].f && celas[segundaCela].d >= celas[y].d && celas[segundaCela].co >= celas[y].co-1 && celas[segundaCela].i >= celas[y].i && celas[segundaCela].s >= celas[y].s && celas[segundaCela].ca >= celas[y].ca){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);

                    } else if(celas[segundaCela].f >= celas[y].f && celas[segundaCela].d >= celas[y].d && celas[segundaCela].co >= celas[y].co && celas[segundaCela].i >= celas[y].i-1 && celas[segundaCela].s >= celas[y].s && celas[segundaCela].ca >= celas[y].ca){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);

                    } else if(celas[segundaCela].f >= celas[y].f && celas[segundaCela].d >= celas[y].d && celas[segundaCela].co >= celas[y].co && celas[segundaCela].i >= celas[y].i && celas[segundaCela].s >= celas[y].s-1 && celas[segundaCela].ca >= celas[y].ca){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);

                    } else if(celas[segundaCela].f >= celas[y].f && celas[segundaCela].d >= celas[y].d && celas[segundaCela].co >= celas[y].co && celas[segundaCela].i >= celas[y].i && celas[segundaCela].s >= celas[y].s && celas[segundaCela].ca >= celas[y].ca-1){
                        inserirAresta(grafoPersonagem, segundaRodada, celas[y].n);
                    }
                }
            }
        }

        // remoções
        for(int y=0; y < nCelas; y++){
            // fazer um for pra primeira e segunda celas e verificar pode ser a solucao.
            if(temAresta(grafoPersonagem, primeiraCela, celas[y].n) == 0 && temAresta(grafoPersonagem, segundaRodada, celas[y].n) == 0){
                int aux = buscarVetor(copiaCelas, auxCelas, celas[y].n);
                if(aux != -1){
                    removerVetor(copiaCelas, aux, auxCelas);
                    auxCelas--;
                    y--;
                }
            }
        }

        // liberação da memória
        destruirGrafo(grafoPersonagem);
    }

    // impressões
    for(int x=0; x < auxCelas; x++){
        printf("%s\n", copiaCelas[x].nome);
    }
    if(auxCelas <= 0){
        printf("Impossivel terminar em duas rodadas.");
    }

    // liberação da memória
    free(celas);
    free(copiaCelas);
    free(personagens);

    return 0;
}