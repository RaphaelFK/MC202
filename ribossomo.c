#include <stdio.h>
#include <stdlib.h>

typedef struct transcricao {
    char dna;
    char rna;
    int numero; // para identificar o numero de vezes que a transcricao foi realizada e ser usado, posteriormente, nos ids
} Transcricao;

void registrar(Transcricao transcricoes[], char dna[], char rna[], int *total){
    /* registra os processos de transcricao atraves do fornecimento de duas listas que relacionam os dna e rna padroes da especie */
    /* a variavel total serve para armazenar o numero total de transcricoes registradas */
    for (int i=0; dna[i] != '\0'; i++){
        Transcricao transcricao;
        transcricao.dna = dna[i];
        transcricao.rna = rna[i];
        transcricao.numero = -1;
        transcricoes[i] = transcricao;
        *total += 1;
    }
}

int main(){
    // definicao das variaveis
    char dna_padrao[25], rna_padrao[25], *segmento, *segmentoTranscrito;
    int tamanho = 0, *idsTranscricao, total = 0;
    Transcricao transcricoes[25];

    // leitura dos dna e rna padroes da especie
    scanf("%s ", dna_padrao);
    scanf("%s ", rna_padrao);

    // registro das transcricoes
    registrar(transcricoes, dna_padrao, rna_padrao, &total);

    // leitura do tamanho do segmento de dna
    scanf("%d ", &tamanho);

    // alocacao de memoria do segmento e leitura do mesmo
    segmento = malloc((tamanho * 2) * sizeof(char));
    scanf("%s ", segmento);

    // alocacao do ponteiro que indicara os ids de cada transcricao e do ponteiro do segmento transcrito
    idsTranscricao = malloc(tamanho * sizeof(int));
    segmentoTranscrito = malloc(tamanho * sizeof(char));

    // identificacao do registro para a transcricao correta de cada base do dna, realizacao da transcricao e registro dos ids
    for (int i=0; segmento[i] != '\0'; i++){
        for (int j=0; j < total; j++){
            if (segmento[i] == transcricoes[j].dna){
                segmentoTranscrito[i] = transcricoes[j].rna;
                transcricoes[j].numero += 1;
                idsTranscricao[i] = transcricoes[j].numero;
            }
        }
    }

    // impressoes
    printf("ID:\t");
    for (int i=0; i < tamanho; i++){
        printf("\t%d", idsTranscricao[i]);
    }

    printf("\nDNA:");
    for (int i=0; i < tamanho; i++){
        printf("\t%c", segmento[i]);
    }

    printf("\n");
    printf("\t");
    for (int i=0; i < tamanho; i++){
        printf("\t|");
    }

    printf("\nRNA:");
    for (int i=0; i < tamanho; i++){   
        printf("\t%c", segmentoTranscrito[i]);
    }

    // liberacao da memoria
    free(segmento);
    free(idsTranscricao);
    free(segmentoTranscrito);

    return 0;
}