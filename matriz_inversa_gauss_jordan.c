/*
 * File:   calculo_matriz_inversa.c
 * Author: Anderson S. Silva & Mariana G. Rodrigues.
 *
 * Created on 11 de Abril de 2019, 14:02
 */

#include <stdio.h>
#include <stdlib.h>

void imprimeMatriz(double **m, int linha, int coluna) {//criei essa função para tirar as impressoes da matriz lá da função main
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++)
            printf(" %05.2lf ", m[i][j]); //coloquei para imprimir com no maximo 5 caracteres, incluindo o ponto decimal. Caso o número seja pequeno e não ocupe 5 caracteres, colocar zeros a esqueda para preencher.
        printf("\n");
    }
}

int main() {
    printf("Bem vindo(a)! \nEsse é um programa que realiza o cálculo da matriz inversa proveniente de uma matriz quadrada.\n\n");
    printf("Localizando arquivo 'matriz.txt'...\n\n");
    double relacao = 0.0; //relação deve ser double
    FILE *arq = NULL;
    FILE *arqsaida = NULL;
    arq = fopen("matriz.txt", "r"); //Procurando arquivo 'matriz.txt' para ser aberto.
    int x[85], linha = 0, coluna = 0; //Vetor com tamanho suficiente para suprir o programa.
    char t[800];
    if (arq == NULL) {//Arquivo nulo nao será aberto e encerrará o programa.
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    int i = 0;
    /*
    Boa prática: uso da função feof(FILE *ponteiro_arquivo)
    como auxiliar na detecção de final do arquivo atingido
    pelo fgetc(). A função feof() retorna != 0 caso tenha
    atingido o final do arquivo...
     */
    while (feof(arq) == 0) {
        fscanf(arq, "%i\n", &x[i]); //pega 3 inteiros inicialmente
        i++;
    }
    fclose(arq); //Fechei o arquivo após ler seus dados e abri novamente para printar seus dados.
    arq = fopen("matriz.txt", "r"); // "r" para apenas ler.
    for (int p = 0; feof(arq) == 0; p++) {
        t[p] = fgetc(arq); // Ler 1 caracter do arquivo aberto
        if (t[p] == '\n') { //conta linha
            linha++;
        }
    }
    i = i / linha;
    coluna = i; //conta coluna
    printf("Tamanho de linhas: %i\nTamanho de colunas: %i\n\n", linha, coluna); // Imprimindo a quantidade de linhas e colunas.
    double **matriz = NULL;
    matriz = (double**) malloc(linha * sizeof (double*));
    for (int j = 0; j < linha; j++) {
        matriz[j] = (double*) malloc(coluna * 2 * sizeof (double)); //já deve ser alocado memória suficiente para colocar a matriz identidade também
    }
    fclose(arq); //FEECHA
    arq = fopen("matriz.txt", "r"); //AAAAABRE
    while (feof(arq) == 0) {
        for (int k = 0; k < linha; k++) {
            for (int p = 0; p < coluna; p++) {
                fscanf(arq, "%lf", &matriz[k][p]);// Criando matriz com o conteudo do arquivo
            }
        }
    }
    printf("Matriz recebida do arquivo\n");
    imprimeMatriz(matriz, linha, coluna); //Imprime a matriz criada pelo arquivo!
    //Aumentando a Matriz de Identidade do Pedido
    for (int p = 0; p < linha; p++) {
        for (int o = 0; o < coluna; o++) {//O indice do vetor/matriz inicia em zero e ele vai até n-1, sendo n o tamanho do vetor (ou quantidade de linhas e colunas)
            if (p == o) {
                matriz[p][o + coluna] = 1;
            } else {
                matriz[p][o + coluna] = 0;
            }
        }
    }
    printf("\nAgora com a identidade\n");
    imprimeMatriz(matriz, linha, coluna * 2); //lembrando que agora tem o dobro da coluna
    for (int i = 0; i < linha; i++) {
        if (matriz[i][i] == 0.0) {
            printf("Erro matemático!");
            exit(0);
        }
        for (int j = 0; j < coluna; j++) {
            if (i != j) {
                relacao = matriz[j][i] / matriz[i][i];
                for (int k = 0; k < 2 * coluna; k++) {//aqui tem ir até o final da matriz aumentada
                    matriz[j][k] = matriz[j][k] - relacao * matriz[i][k];
                }
            }
        }
    }
    imprimeMatriz(matriz, linha, coluna * 2);
    //Operação de linha para fazer diagonal principal para 1
    for (int i = 0; i < linha; i++) {
        relacao = matriz[i][i]; //a variavel relação deve ficar aqui para não ser sobreescrita
        for (int j = 0; j < 2 * coluna; j++) {
            matriz[i][j] = matriz[i][j] / relacao; //antes vc tinha colocado matriz[i][i] aqui no lugar de relação. Isso tava sobreescrevendo o valor de matriz[i][i], fazendo com que o resultado das divisões dessem errado
        }
    }
    imprimeMatriz(matriz, linha, coluna * 2);
    //Exibir matriz inversa
    printf("\nA matriz inversa é: \n");
    for (int i = 0; i < linha; i++) {
        for (int j = linha; j < 2 * coluna; j++) {
            printf("%.3lf\t", matriz[i][j]);
        }
        printf("\n");
    }
    arqsaida = fopen("matrizinversa.txt", "w");
    for (int i = 0; i < linha; i++) {
        for (int j = linha; j < 2 * coluna; j++) {
            fprintf(arqsaida, "%.3lf\t", matriz[i][j]);
            //fprintf(arqsaida, " ");
        }
        fprintf(arqsaida, "\n");
    }
    return 0;
}
