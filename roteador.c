#include <stdio.h>
#include <stdlib.h>

#define PAI(x) ((x-1)/2)
#define F_ESQ(x) (2*x+1)
#define F_DIR(x) (2*x+2)

typedef struct{
    int id;
    int prioridade;
    int incremento;
} Pacote;

typedef struct{
    Pacote *v;
    int n, tamanho;
} FP;
typedef FP *p_fp;


/* Cria um novo pacote com os parâmetros fornecidos e o retorna. */
Pacote criarPacote(int id, int prioridade, int incremento){
    Pacote novo;
    novo.id = id;
    novo.prioridade = prioridade;
    novo.incremento = incremento;
    return novo;
}

/* Realiza a troca de posições entre dois pacotes fornecidos. */
void troca(Pacote *x, Pacote *y){
    Pacote i = *x;
    *x = *y;
    *y = i;
}

/* Cria uma fila prioritária de tamanho fornecido, realizando a alocação dinâmica da memória. */
p_fp criarFilaprio(int tamanho){
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tamanho * sizeof(Pacote));
    fprio->n = 0;
    fprio->tamanho = tamanho;
    return fprio;
}

/* Sobe um elemento indicado no heap fornecido. */
void sobeNoHeap(p_fp fprio, int k){
    if(k > 0 && fprio->v[PAI(k)].prioridade < fprio->v[k].prioridade){
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        sobeNoHeap(fprio, PAI(k));
    }
}

/* Desce um elemento indicado no heap fornecido. */
void desceNoHeap(p_fp fprio, int k){
    int maiorFilho;
    if(F_ESQ(k) < fprio->n){
        maiorFilho = F_ESQ(k);
        if(F_DIR(k) < fprio->n && fprio->v[F_ESQ(k)].prioridade < fprio->v[F_DIR(k)].prioridade){
            maiorFilho = F_DIR(k);
        }
        if(fprio->v[k].prioridade < fprio->v[maiorFilho].prioridade){
            troca(&fprio->v[k], &fprio->v[maiorFilho]);
            desceNoHeap(fprio, maiorFilho);
        }
    }
}

/* Insere um pacote em um heap fornecido. */
void inserir(p_fp fprio, Pacote pacote){
    fprio->v[fprio->n] = pacote;
    fprio->n++;
    sobeNoHeap(fprio, fprio->n - 1);
}

/* Retorna o valor máximo de um heap fornecido e remove-o da estrutura. */
Pacote extraiMaximo(p_fp fprio){
    Pacote pacote = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desceNoHeap(fprio, 0);
    return pacote;
}

/* Realiza a liberação da memória de uma fila prioritária alocada. */
void destruirFilaprio(p_fp fprio){
    free(fprio->v);
    free(fprio);
}

/** Muda a prioridade de um elemento em uma fila prioritária 
 * para um valor fornecido e faz os ajustes necessários à fila. */
void mudarPrioriade(p_fp fprio, int k, int valor){
    if(fprio->v[k].prioridade < valor){
        fprio->v[k].prioridade = valor;
        sobeNoHeap(fprio, k);
    } else {
        fprio->v[k].prioridade = valor;
        desceNoHeap(fprio, k);
    }
}


int main(){
    // inicialização das variáveis
    int k, m, id, prioridade, incremento, ticks=1, entradas=0;
    scanf("%d %d ", &k, &m);
    p_fp roteador = criarFilaprio(m);

    // leituras e processos da fila
    while(scanf("%d %d %d ", &id, &prioridade, &incremento) != EOF){
        if(id == 0 && prioridade == 0 && incremento == 0){ // se detectar um tick
            printf("TICK %d\n", ticks);
            Pacote aux;
            int auxEntradas = entradas;
            for(int i=0; i < k && i < auxEntradas; i++){
                aux = extraiMaximo(roteador);
                printf("%d %d %d\n", aux.id, aux.prioridade, aux.incremento);
                entradas--;
            }
            printf("\n");

            for(int i=0; i < entradas; i++){
                int inc = roteador->v[i].prioridade + roteador->v[i].incremento;
                mudarPrioriade(roteador, i, inc);
            }
            ticks++;

        } else { // entrada de um pacote comum
            if(entradas < m){
                Pacote pacote = criarPacote(id, prioridade, incremento);
                inserir(roteador, pacote);
                entradas++;
            }
        }
    }

    // liberação da memória
    destruirFilaprio(roteador);

    return 0;
}