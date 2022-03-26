#include <stdio.h>
#include <string.h>

int indice(int numero, int lista[], int lenght){
    for (int i = 0; i < lenght; i++){
        if (lista[i] == numero){
            return i;
        }
    }
    return 0;
}

void grupoDeAmigos(int a, int b, int lista[]) {
    int conta = (b-a+1)/2;
    int contador = b;
    for (int i = a; i < conta + a; i++) {
        int aux = lista[i];
        lista[i] = lista[contador];
        lista[contador] = aux;
        contador -= 1;
    }
}

void esperar(int a, int b, int lista[]){
    int conta = b-a;
    int aux = lista[a];
    for (int i = a; i < conta + a; i++){
        lista[i] = lista[i+1];
    }
    lista[b] = aux;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    /*Criacao de uma lista com todos os números*/
    int lista[100000];
    for (int i = 0; i < n; i++) {
        lista[i] = i + 1;
    }

    for (int i = 0; i < m; i++) {

        int identificador, entradaA, entradaB;
        scanf("%d %d %d", &identificador, &entradaA, &entradaB);

        int indiceA, indiceB;
        indiceA = indice(entradaA, lista, n);
        indiceB = indice(entradaB, lista, n);

        if (identificador == 1) {
            grupoDeAmigos(indiceA, indiceB, lista);
        } else {
            esperar(indiceA, indiceB, lista);
        }
    }

    /* Impressao da lista final */
    for (int i = 0; i < n; i++) {
        if (i == n-1){
           printf("%d", lista[i]); 
        } else {
            printf("%d", lista[i]); 
            printf(" ");
        }
    }

    return 0;
}