#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define num_cidades 5
#define ind_pop 20

void imprimirpop(int **matriz) {
    for (int i = 0; i < ind_pop; i++) {
        for (int j = 0; j <= num_cidades; j++) {
            printf("%i\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void criar_populacao(int **individuo) {
    int i, j, temp;
    printf("\n\n-------------------------------------------------\n\n");
    srand(time(NULL)); //iniciar uma "semente" (seed) aleatória ==> srand = seed randômica
    for (int a = 0; a < ind_pop; a++) {//percorre as linhas da matriz
        for (int b = 0; b <= num_cidades; b++) {//percorre as colunas da matriz
            individuo[a][b] = b + 1;
            if (b == num_cidades) {
                individuo[a][b] = 1;
            }
        }
        for (int c = 1; c < num_cidades; c++) { //començando da segunda coluna, por isso c=1. A primiera fica intacta com os 1's
            j = 1 + rand() % (num_cidades - 1); //gera números aleatorios de 1 até num_cidades-1;
            temp = individuo[a][c];
            individuo[a][c] = individuo[a][j];
            individuo[a][j] = temp;
        }
    }
    printf("\nPopulação Aleatorizada: \n");
    imprimirpop(individuo); //chamei a função de impressão aqui, mas poderia ser na main (linha 71)
}

void elitismo(int **matrizpop, double **tabelacaixeiro) {
    double *vetor_dist = NULL;
    vetor_dist = (double *) malloc(ind_pop * sizeof (double));
    printf("Dessgraça");
    for (int i = 0; i < ind_pop; i++) {
        for (int j = 0; j < num_cidades; j++) {
            vetor_dist[i] += tabelacaixeiro[matrizpop[i][j]][matrizpop[i][j + 1]];
        }
    }
    printf("\n\n**********************************************\n\n");
    for (int i = 0; i < ind_pop; i++) {
        printf("%lf", vetor_dist[i]);
    }
}

int main() { // No main abaixo está sendo implementado a situação que o usuário quer resolver.
    //int individuo[ind_pop][num_cidades]; //criando a matriz de população
    int **individuo = NULL;
    individuo = (int **) malloc(ind_pop * sizeof (int *));
    for (int i = 0; i < ind_pop; i++) {
        individuo[i] = (int *) malloc(num_cidades * sizeof (int));
    }
    printf("Número de cidades: 5\n\n");
    double **dist_cidades;
    dist_cidades = (double **) malloc(num_cidades * sizeof (double *));
    for (int i = 0; i < num_cidades; i++) {
        dist_cidades[i] = (double *) malloc(num_cidades * sizeof (double));
    }
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            if (j == i) {
                dist_cidades[i][j] = 0;
                continue;
            }
            if (j > i) {
                printf("Distância da cidade [%i] até a cidade [%i]\t", i + 1, j + 1);
                scanf("%lf", &dist_cidades[i][j]);
            } else
                dist_cidades[i][j] = dist_cidades[j][i];
        }
    }
    printf("\n");
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            printf("%.1lf\t", dist_cidades[i][j]);
        }
        printf("\n");
    }
    criar_populacao(individuo);
    elitismo(individuo, dist_cidades);
    return 0;
}
