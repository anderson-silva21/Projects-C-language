#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define num_cidades 20
#define ind_pop 20
#define num_geracoes 20

void desaloc(int **individuo, double **dist_cidades) { //função que desaloca as matrizes
    for (int i = 0; i < ind_pop; i++) {
        free(individuo[i]);
    }
    for (int i = 0; i < num_cidades; i++) {
        free(dist_cidades[i]);
    }
    free(individuo);
    free(dist_cidades);
}

void criar_populacao(int **individuo) {
    int i = 0, j = 0, temp = 0;
    srand(time(NULL)); //iniciar uma "semente" (seed) aleatória ==> srand = seed randômica
    for (int a = 0; a < ind_pop; a++) { //percorre as linhas da matriz
        for (int b = 0; b <= num_cidades; b++) { //percorre as colunas da matriz
            individuo[a][b] = b; //Preenche todos os valores do vetor em ordem crescente, de 0 até numero de cidades
            if (b == num_cidades) { //Faz a última colunas ser 0 ()voltar à cidade inicial
                individuo[a][b] = 0;
            }
        }
        for (int x = 0; x < 100; x++) {
            for (int c = 1; c < num_cidades; c++) { //començando da segunda coluna, por isso c=1. A primiera fica intacta com os 1's
                j = 1 + rand() % (num_cidades - 2); //gera números aleatorios de 1 até num_cidades-1;
                temp = individuo[a][c];
                individuo[a][c] = individuo[a][j]; //Embaralha-se todos os valores que estavam em ordem crescente(permutação) de forma a torna-los aleatórios
                individuo[a][j] = temp;
            }
        }
    }
    printf("\nPopulação Aleatorizada: \n");
    for (int i = 0; i < ind_pop; i++) {
        for (int j = 0; j <= num_cidades; j++) {
            printf("%i   ", individuo[i][j]);
        }
        printf("\n");
    }
}

void elitismo(double *vetor_dist, int **matrizpop, double **tabelacaixeiro) { //função para calcular a aptidão
    for (int i = 0; i < ind_pop; i++) {
        vetor_dist[i] = 0;
        //Calculasse os valores de cada individuo, armazenando-os em um vetor que vai acompanhar os indices de linhas da matriz
        for (int j = 1; j < num_cidades + 1; j++) {
            vetor_dist[i] += tabelacaixeiro[matrizpop[i][j - 1]][matrizpop[i][j]];
        }
    }
}

int selecaoTorneio(int **individuo, double **tabelacaixeiro) { //função que realizará o torneio entre 3 pais
    int qtdSelecionados = 3;
    int indicePai[ind_pop], indiceMelhorPai;
    double *vetor_dist = NULL, menor_dist;
    vetor_dist = (double *) malloc(ind_pop * sizeof (double));
    for (int i = 0; i < qtdSelecionados; i++) {
        indicePai[i] = rand() % (ind_pop - 1); //indica a linha que está o individuo
        vetor_dist[i] = 0; //zerando a distancia do candidato ao pai i
        for (int j = 0; j < num_cidades; j++)
            vetor_dist[i] += tabelacaixeiro[individuo[indicePai[i]][j]][individuo[indicePai[i]][j + 1]];
    } //(não tem problema os pais serem iguais)
    //agora é preciso comparar qual dos "qtdSelecionados" é o melhor individuo;
    menor_dist = vetor_dist[0];
    indiceMelhorPai = indicePai[0]; //supodo inicialmente que o melhor pai é o primeiro dos selecionaodos para o torneio
    for (int i = 0; i < qtdSelecionados; i++) {
        if (vetor_dist[i] < menor_dist) { //caso encontre um individuo com uma rota menor
            menor_dist = vetor_dist[i]; //troca a informação da menor rota
            indiceMelhorPai = indicePai[i]; //guarda o índice do pai com a menor rota
        }
    }
    free(vetor_dist); //desalocando o vetor vetor_dist
    return indiceMelhorPai; //retornando para função main o indice do pai escolhido
}

void ordercross(int indice_pai1, int indice_pai2, int **individuo, int *filho1, int *filho2) {
    int pai1[19], pai2[19]; //Tamanho 19 pois são o números de colunas, pode ser inicializado com [num_cidades - 1] para tornar o programa mais versátil
    for (int i = 0; i <= 19; i++) {
        pai1[i] = individuo[indice_pai1][i + 1];
        pai2[i] = individuo[indice_pai2][i + 1]; // os pais que vão ser usados na função recebem os pais que ganharam o torneio
    }
    int corte1 = 6, corte2 = 13; //Corte para definir os limites do cruzamento de genes(Cross Order)
    for (int i = 0; i < num_cidades - 1; i++) { //Preenche todos os indices com '0'
        filho2[i] = 0;
        filho1[i] = 0;
    }
    for (int i = corte1; i < corte2; i++) { //É passado informações do pai 1 pro filho 1 e do pai 2 pro filho 2 
        filho1[i] = pai1[i];
        filho2[i] = pai2[i];
    }
    //rotacionando os pais
    for (int j = 0; j < corte2; j++) { //Funciona como um "shift", ele arrastará a parte anterior do corte do pro final das colunas, possibilitando a comparação de genes quando passarmos de pai pra filho

        int tmp1 = pai1[0]; //Salva a primeira casa em uma variável temporária
        int tmp2 = pai2[0];
        for (int i = 0; i < num_cidades - 1; i++) { //Arrastos todos 1 casa pra esquerda
            pai1[i] = pai1[i + 1];
            pai2[i] = pai2[i + 1];
        }
        pai1[num_cidades - 2] = tmp1; // preenche a última casa com a variável temporária, fazendo com que o programa salve o primeiro indice, arraste o vetor pra esquerda e coloca o valor da temporária no final
        pai2[num_cidades - 2] = tmp2;
    }
    //rotacionando os filhos
    for (int j = 0; j < corte2; j++) { //Mesmo processo  da rotação dos pais
        int tmp1 = filho1[0];
        int tmp2 = filho2[0];
        for (int i = 0; i < num_cidades - 1; i++) {
            filho1[i] = filho1[i + 1];
            filho2[i] = filho2[i + 1];
        }
        filho1[num_cidades - 2] = tmp1;
        filho2[num_cidades - 2] = tmp2;
    }
    //fim rotacao filhos
    int k = 0;
    for (int i = 0; i < corte2 - 1; i++, k++) {
inicio1:
        for (int j = corte2 - 1; j < num_cidades - 1; j++) { //Essa parte fará a comparação dos genes por meio do Cross Order
            if (pai2[k] == filho1[j]) {
                k++;
                goto inicio1;
            }
        }
        filho1[i] = pai2[k];
    }
    int p = 0;
    for (int i = 0; i < corte2 - 1; i++, p++) {
inicio2:
        for (int j = corte2 - 1; j < num_cidades - 1; j++) { //Essa parte fará a comparação dos genes por meio do Cross Order
            if (pai1[p] == filho2[j]) {
                p++;
                goto inicio2;
            }
        }
        filho2[i] = pai1[p];
    }
    //DESrotacionando os filhos
    for (int j = 0; j < corte1; j++) {
        int tmp1 = filho1[0];
        int tmp2 = filho2[0];
        for (int i = 0; i < num_cidades - 1; i++) { //Operação "inversa" ao rotacionamento do filho, jogando a prmeira parte (0 até corte 1) para o final das colunas
            //if (i > 0 && i < num_cidades) {
            filho1[i] = filho1[i + 1];
            filho2[i] = filho2[i + 1];
            //}
        }
        filho1[num_cidades - 2] = tmp1;
        filho2[num_cidades - 2] = tmp2;
    }
    for (int i = num_cidades - 2; i >= 0; i--) { //
        filho1[i + 1] = filho1[i]; //Arrasta o vetor 1 casa pra direita
        filho2[i + 1] = filho2[i]; //
    } //                                                                        // Preencher a primeira e última colunas com a cidade de origem 0
    filho1[0] = 0; //
    filho2[0] = 0; //
    filho1[21] = 0;
    filho2[21] = 0;
}

void mutacao(int *filho1, int *filho2) { //Função que alterará aleatóriamente os genes dos filhos
    int aleatorio1 = 0,
            aleatorio2 = 0,
            tempo1 = 0,
            tempo2 = 0;
    int gene1filho1 = 0;
    int gene2filho1 = 0;
    int gene1filho2 = 0;
    int gene2filho2 = 0;
    srand(time(NULL));
    aleatorio1 = rand() % 100; //Chance de acontecer mutação
    sleep(1);
    aleatorio2 = rand() % 100;
    if (aleatorio1 == 1) {
        srand(time(NULL));
        gene1filho1 = 1 + rand() % (num_cidades - 2); //Gênes que serão trocados
        sleep(1);
        srand(time(NULL));
        gene2filho1 = 1 + rand() % (num_cidades - 2); //Gênes que serão trocados        
        tempo1 = filho1[gene1filho1];
        filho1[gene1filho1] = filho1[gene2filho1];
        filho1[gene2filho1] = tempo1;
    }
    srand(time(NULL));
    if (aleatorio2 == 1) {
        gene1filho2 = 1 + rand() % (num_cidades - 2); //Gênes que serão trocados        
        srand(time(NULL));
        gene2filho2 = 1 + rand() % (num_cidades - 2); //Gênes que serão trocados      
        tempo2 = filho2[gene1filho2];
        filho2[gene1filho2] = filho2[gene2filho2];
        filho2[gene2filho2] = tempo2;
    }
}

void reposicaopais(double *vetor_dist, int **individuo, int *filho1, int *filho2) { //Função que fara a reposição dos filhos novos pelos piores da população anterior
    int indicemaiscaro1 = 0;
    int indicemaiscaro2 = 0;
    int indice1 = 0;
    int indice2 = 0;
    for (int i = 0; i < ind_pop; i++) {
        if (i == 0) {
            indicemaiscaro1 = vetor_dist[i];
            indice1 = i; //Achará quem é o individuo mais caro
        } else {
            if (vetor_dist[i] > indicemaiscaro1) {
                indicemaiscaro1 = vetor_dist[i];
                indice1 = i;
            }
        }
    }
    for (int i = 0; i < ind_pop; i++) {
        if (i == 0 || indicemaiscaro2 == indicemaiscaro1) {
            indicemaiscaro2 = vetor_dist[i];
            indice2 = i; //Achará o segundo individuo mais caro
        } else {
            if (vetor_dist[i] > indicemaiscaro2 || indicemaiscaro2 == indicemaiscaro1) {
                indicemaiscaro2 = vetor_dist[i];
                indice2 = i;
            }
        }
    }
    for (int i = 0; i <= 19; i++) {
        individuo[indice1][i] = filho1[i]; //Fará a reposição dos filhos novos peslos indivíduo mais caros da população anterios
        individuo[indice2][i] = filho2[i];
    }
}

int melhorindividuoprog(int melhorindividuo, int indicemelhorindividuo, double *vetor_dist) {
    for (int i = 0; i < ind_pop; i++) {
        if (i == 0) {
            melhorindividuo = vetor_dist[i];
            indicemelhorindividuo = i;
        } else { //Achará o indivíduo e o indice mais barato
            if (vetor_dist[i] < melhorindividuo) {
                melhorindividuo = vetor_dist[i];
                indicemelhorindividuo = i;
            }
        }
    }
    return melhorindividuo;
}

int main() { // No main abaixo está sendo implementado a situação que o usuário quer resolver.
    int **individuo = NULL,
            indicePai1,
            indicePai2,
            *filho1,
            *filho2,
            condicaodeparada = 0, //São inicializadas todas as variáveis do tipo int que precisaremos
            melhorindividuo, //Importante iniciar todas no mais para permitir uma comnicação mais fácil entre as funções
            indicemelhorindividuo,
            vezesdemutacao = 0,
            melhorindividuofuncao = 0;
    filho1 = (int *) malloc(21 * sizeof (int)); // alocação dinâmica do filho 1 e do filho 2
    filho2 = (int *) malloc(21 * sizeof (int)); // alocação dinâmica é importante foi ao invez de vetor, conseguimos trabalhar com os indices mesmo sobrando memórias(ou indices a mais no final)
    // Permite que todas as funções modifiquem apenas 1 variável, facilitando a comunicação entre elas  
    individuo = (int **) malloc(ind_pop * sizeof (int *));
    for (int i = 0; i < ind_pop; i++) { //Alocação dinâmica das matrizes necessárias ao decorrer do programa
        individuo[i] = (int *) malloc((num_cidades + 1) * sizeof (int));
    }
    double **dist_cidades = NULL; //Permite que todas as funções utilize apenas 1 matriz na memória no código todo, facilitando a comunicação entre elas
    dist_cidades = (double **) malloc(num_cidades * sizeof (double *));
    for (int i = 0; i < num_cidades; i++) { //Alocação dinâmica das matrizes necessárias ao decorrer do programa
        dist_cidades[i] = (double *) malloc(num_cidades * sizeof (double));
    }
    FILE *arq = NULL; // Ponteiro para acessar arquivo .txt
    arq = fopen("distancia_cidades.txt", "r"); // Será buscado um arquivo de nome 'dist_cidades.txt' e está apenas para leitura
    if (arq == NULL) { //Arquivo nulo nao será aberto e encerrará o programa.
        printf("Erro ao abrir o arquivo\n\n");
        exit(1);
    }
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            fscanf(arq, "%lf ", &dist_cidades[i][j]); //Leitura de todos os dados do arquivo
        }
    }
    double *vetor_dist = NULL;
    vetor_dist = (double *) malloc(ind_pop * sizeof (double)); //Alocação dinâmica do vetor que permitirá cálcular a aptidão de cada individuo
    //------------------------------------------------------------------------------
    criar_populacao(individuo); //Criando uma população em ordem aleatória
    //Ela só precisa ser criada uma vez, pois o código passará a atualizar esa matriz e reutilizala para continuar atualizado até um resultado                                                                                                  
    for (int i = 0; i < num_geracoes; i++) {
        elitismo(vetor_dist, individuo, dist_cidades); //Função que permite o cáculo do individuos com os menores valores(aptidão)        
        /* printf("\n\nSomas:\n\n|");
         for (int k = 0; k < ind_pop; k++) {
             printf("%.1lf|", vetor_dist[k]);
         }
         */
        indicePai1 = selecaoTorneio(individuo, dist_cidades); //Torneio entre 3 pais para ser escolhido 1 e passar seus gênes
        indicePai2 = selecaoTorneio(individuo, dist_cidades);
        //do while para não escolher dois pais iguais, fazendo com que o programa não tenha muita diversidade e piorando o resultado
        ordercross(indicePai1, indicePai2, individuo, filho1, filho2); //Função que permite que os pais passem os gênes para os filhos 1 e 2 por meio do Order Cross(OX)
        mutacao(filho1, filho2); //Função que tem uma chance de realizar uma mutação nos filhos 1 e 2 
        reposicaopais(vetor_dist, individuo, filho1, filho2); //Função que permite atualizar a população substituindo os filhos 1 e 2 pelos 2 piores da última população
        printf("\nPopulação: \n");
        for (int i = 0; i < ind_pop; i++) {
            for (int j = 0; j <= num_cidades; j++) { // Trackear os resultados do programa
                printf("%i   ", individuo[i][j]);
            }
            printf("\n");
        }
        for (int i = 0; i < ind_pop; i++) {
            if (i == 0) {
                melhorindividuo = vetor_dist[i];
                indicemelhorindividuo = i;
            } else { //Achará o indivíduo e o indice mais barato
                if (vetor_dist[i] < melhorindividuo) {
                    melhorindividuo = vetor_dist[i];
                    indicemelhorindividuo = i;
                }
            }
        }
        printf("melhor individuo: %i \n", indicemelhorindividuo); // Trackear os resultados do programa   
        for (int j = 0; j <= 19; j++) {
            printf("%i ", individuo[indicemelhorindividuo][j]); //Printa melhor indivíduo
        }
    }
    /*  for (int i = 0; i < ind_pop; i++) {
           if (i == 0) {
               melhorindividuo = vetor_dist[i];
               indicemelhorindividuo = i;
           } else {
               if (vetor_dist[i] < melhorindividuo) {                                      //Mostrará o melhor indivíduo
                   melhorindividuo = vetor_dist[i];
                   indicemelhorindividuo = i;
               }
       }
   }
       printf("\nPopulação Final: \n");
       for (int i = 0; i < ind_pop; i++) {
           for (int j = 0; j <= num_cidades; j++) {                                    //Printa a populaçao final
               printf("%i   ", individuo[i][j]);
          }
           printf("\n");
     }
    // printf("\nMelhor individuo: \n");

      // for (int j = 0; j <= 19; j++) {
       //   printf("%i ", individuo[indicemelhorindividuo][j]) ;                         //Printa melhor indivíduo
        //}
     */
    printf("\n\n\nValor do individuo: %lf", vetor_dist[indicemelhorindividuo]);
    desaloc(individuo, dist_cidades);
    free(filho1); //Desalocando os espaços na memória reservados pelos malloc's
    free(filho2);
    return 0;
}
