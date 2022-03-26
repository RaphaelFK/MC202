#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"

int **calcularAltitudes(int m, int n, int seed){
    /* cria uma matriz de altitudes representando o relevo de um mundo */

    // alocacao da memoria
    int** altitudes;
    altitudes = malloc(m * sizeof(int*));
    for (int i=0; i<m; i++){
        altitudes[i] = malloc(n * sizeof(int*));
    }

    // calculo da altitude de cada coordenada
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            altitudes[i][j] = (seed * (202 + i + j) + 12345 + i + j) % 256;
        }
    }
    return altitudes;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed){
    /* cria um novo mundo representado por uma matriz de blocos alocada dinamicamente */

    // alocacao da memoria
    Bloco ***mundo;
    mundo = malloc(m * sizeof(Bloco*));
    for (int i=0; i<m; i++){
        mundo[i] = malloc(n * sizeof(Bloco*));
        for (int j=0; j<n; j++){
            mundo[i][j] = malloc(256 * sizeof(Bloco*));
        }
    }

    // calculo do numero de cada bloco do mundo gerado
    for (int x=0; x<m; x++){
        for (int z=0; z<n; z++){
            for (int y=0; y<256; y++){
                if (y > altitudes[x][z]){
                    Bloco bloco;
                    bloco.numero = 21;
                    mundo[x][z][y] = bloco;

                } else {
                    Bloco bloco;
                    bloco.numero = (seed * (202 + x + y + z) + x + y + z) % 33;
                    mundo[x][z][y] = bloco;
                }
            }  
        }
    }
    return mundo;
}

double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos){
    /* explora o mapa de um mundo e devolve o tempo necessário para minerar todo ele. além disso, devolve a quantidade de alguns minérios de interesse */

    // identificacao e contagem de cada bloco do mundo
    for (int x=0; x<m; x++){
        for (int z=0; z<n; z++){
            for (int y=0; y<256; y++){
                if (mundo[x][z][y].numero == 0){ //diamante
                    *qtdDiamante += 1;
                    *qtdBlocos += 1;
                } else if (mundo[x][z][y].numero < 3){ //ouro
                    *qtdOuro += 1;
                    *qtdBlocos += 1;
                } else if (mundo[x][z][y].numero < 6){ //ferro
                    *qtdFerro += 1;
                    *qtdBlocos += 1;
                } else if (mundo[x][z][y].numero < 12){ //pedra
                    *qtdBlocos += 1;
                } else if (mundo[x][z][y].numero < 21){ //terra
                    *qtdBlocos += 1;
                }
            }
        }
    }

    // calculo do tempo total
    double tempoTotal = 0;
    tempoTotal = tempoPorBloco * (*qtdBlocos);
    return tempoTotal;
}

int main(){
    // definicao das variaveis
    int m, n, seed, qtdDiamante=0, qtdOuro=0, qtdFerro=0, qtdBlocos=0;
    float tempoPorBloco=0;
    
    // leitura dos dados
    scanf("%i %i ", &m, &n);
    scanf("%i ", &seed);
    scanf("%f ", &tempoPorBloco);

    // definicao das variaveis e chamada das funcoes
    int **altitudes = calcularAltitudes(m, n, seed);
    Bloco ***mundo = criarMundo(m, n, altitudes, seed);;
    float tempoTotal = explorarMundo(mundo, m, n, altitudes, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);
    
    // liberacao de memoria
    for (int i=0; i<m; i++){
        free(altitudes[i]);
    }
    free(altitudes);

    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            free(mundo[i][j]);
        }
        free(mundo[i]);
    }
    free(mundo);

    // impressoes
    printf("Total de Blocos: %i\n", qtdBlocos);
    printf("Tempo total: %.2fs\n", tempoTotal);
    printf("Diamantes: %i\n", qtdDiamante);
    printf("Ouros: %i\n", qtdOuro);
    printf("Ferros: %i", qtdFerro);

    return 0;
}