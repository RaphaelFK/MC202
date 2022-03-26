#include <stdio.h>
#include <string.h>

float calculaImpostoMensal(float rendimentoMensal){
    float imposto = 0;

    if (rendimentoMensal <= 1499.15){
        imposto = 0;
    } else if ((1499.15 < rendimentoMensal) && (rendimentoMensal <= 2246.75)){
        imposto = (rendimentoMensal - 1499.15) * 0.075;
    } else if ((2246.75 < rendimentoMensal) && (rendimentoMensal <= 2995.70)){
        imposto = 56.07 + (rendimentoMensal - 2246.75) * 0.15;
    } else if ((2995.70 < rendimentoMensal) && (rendimentoMensal <= 3743.19)){
        imposto = 56.07 + 112.3425 + (rendimentoMensal - 2995.70) * 0.225;
    } else if (3743.19 < rendimentoMensal){
        imposto = 56.07 + 112.3425 + 168.18525 + (rendimentoMensal - 3743.19) * 0.275;
    }
    return imposto;
}

float calculaImpostoAnual(float rendimentoAnual){
    float imposto = 0;

    if (rendimentoAnual <= 18000){
        imposto = 0;
    } else if ((18000.00 < rendimentoAnual) && (rendimentoAnual <= 26400.00)){
        imposto = (rendimentoAnual - 18000.00) * 0.075;
    } else if ((26400.00 < rendimentoAnual) && (rendimentoAnual <= 36000.00)){
        imposto = 630.00 + (rendimentoAnual - 26400.00) * 0.15;
    } else if ((36000.00 < rendimentoAnual) && (rendimentoAnual <= 44400.00)){
        imposto = 630.00 + 1440.00 + (rendimentoAnual - 36000.00) * 0.225;
    } else if (44400.00 < rendimentoAnual){
        imposto = 630.00 + 1440.00 + 1890.00 + (rendimentoAnual - 44400.00) * 0.275;
    }
    return imposto;
}

int main(){
    int n;
    scanf("%d ", &n);

    float rendimentos[1000][13];
    float impostos[1000][15];
    float abatimentos[1000];

    /* leitura dos dados e organização em matrizes */
    for (int f = 0; f < n; f++){
        for (int m = 0; m < 12; m++){
            scanf("%f ", &rendimentos[f][m]);
            rendimentos[f][12] += rendimentos[f][m];
        }
    }

    for (int f = 0; f < n; f++){
        scanf("%f ", &abatimentos[f]);
    }

    /* calculo dos impostos mensais */
    for (int f = 0; f < n; f++){
        for (int m = 0; m < 12; m++){
            impostos[f][m] = calculaImpostoMensal(rendimentos[f][m]);
        }
    }

    /* calculo do imposto retido, anual e dos ajustes */
    
    /* imposto retido total (impostos[f][12]) */
    for (int f = 0; f < n; f++){
        impostos[f][12] = 0;

        for (int m = 0; m < 12; m++){
            impostos[f][12] += impostos[f][m];
        }
    }

    /* imposto anual (impostos[f][13]) */
    for (int f = 0; f < n; f++){
        impostos[f][13] = calculaImpostoAnual(rendimentos[f][12] - abatimentos[f]);
    }

    /* ajuste (impostos[f][14]) */
    for (int f = 0; f < n; f++){
        impostos[f][14] = impostos[f][13] - impostos[f][12];
    }

    /* impressao das informacoes */
    printf("Jan\tFev\tMar\tAbr\tMai\tJun\tJul\tAgo\tSet\tOut\tNov\tDez\tRetido\tDevido\tAjuste\n");
    for (int f = 0; f < n; f++){
        for (int m = 0; m < 12; m++){
            printf("%.2f\t", impostos[f][m]);
        }
        printf("%.2f\t", impostos[f][12]);
        printf("%.2f\t", impostos[f][13]);
        printf("%.2f\n", impostos[f][14]);
    }

    return 0;
}