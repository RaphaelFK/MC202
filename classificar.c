#include <stdio.h>
#include <string.h>

void ordenar(char lista[100][50], int n){
    /* Funcao que ordena uma lista em ordem alfabética (n e o numero de elementos usados na lista) */
    for (int i = 0; i < n; i++){
        for (int j=i+1; j < n; j++){
            int comparacao = strcmp(lista[i], lista[j]);
            if (comparacao > 0){
                char aux[50];

                strcpy(aux, lista[j]);
                strcpy(lista[j], lista[i]);
                strcpy(lista[i], aux);
            }
        }
    }
}

void homonimos(char lista[100][50], int separadores[100], int totalLista){
    /* identifica homonimos de uma lista ordenada de nomes e imprime-os em ordem alfabetica */
    int auxiliar = 0;

    for (int i = 0; i < totalLista; i++){
        int contador = 0;

        for (int j = 0; j < separadores[i]; j++){
            if (lista[i][j] != lista[i+1][j]){
                contador += 1;
                break;
            }
        }

        if (contador == 0){
            if (auxiliar == 0){
                printf("%s\n", lista[i]);
                auxiliar += 1;
            }
            printf("%s\n", lista[i+1]);

        } else if (contador != 0){
            auxiliar = 0;
        }
    }
}

int main(){
    /* definicao das variaveis */
    int n;
    char palavra[10];
    char nomes[100][50];
    int separadores[100];

    /* leituras iniciais */
    scanf("%d ", &n);
    scanf("%s ", palavra);

    /* leitura dos nomes */
    for (int i = 0; i < n; i++){
        char entrada [30];
        scanf("%s ", entrada);
        strcpy(nomes[i], entrada);
    }

    /* organizacao dos nomes em ordem alfabetica */
    ordenar(nomes, n);

    /* identificacao dos separadores de cada nome */
    for (int i = 0; i < n; i++){
        for (int j = 0; nomes[i][j] != '\0'; j++){
            char separador[] = "_";

            if (*separador == nomes[i][j]){
                separadores[i] = j;
            }
        }
    }

    /* identificacao dos homonimos e impressao */
    homonimos(nomes, separadores, n);

    return 0;
}