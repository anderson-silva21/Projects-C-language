#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 100
#define NUM_CITIES 10
#define NUM_GENERATIONS 1000
#define MUTATION_RATE 0.01

// estrutura para representar um cromossomo
struct chromosome {
    int cities[NUM_CITIES];
    float fitness;
};

// matriz de distâncias entre as cidades
float distance[NUM_CITIES][NUM_CITIES];

// função para calcular a função de aptidão do cromossomo
float calcFitness(struct chromosome* c) {
    float totalDistance = 0;
    // calcular distância total percorrida pelo caixeiro viajante
    for (int i = 0; i < NUM_CITIES-1; i++) {
        int city1 = c->cities[i];
        int city2 = c->cities[i+1];
        // distância entre as cidades
        totalDistance += distance[city1][city2];
    }
    // adicionar distância da última cidade de volta para a primeira
    totalDistance += distance[c->cities[NUM_CITIES-1]][c->cities[0]];
    // retornar aptidão inversa (quanto menor a distância, maior a aptidão)
    return 1.0 / totalDistance;
}

// função para selecionar os pais para o cruzamento
void selection(struct chromosome* population, struct chromosome* parents) {
    int best1 = 0, best2 = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > population[best1].fitness) {
            best2 = best1;
            best1 = i;
        } else if (population[i].fitness > population[best2].fitness) {
            best2 = i;
        }
    }
    // armazenar os dois melhores cromossomos como pais
    parents[0] = population[best1];
    parents[1] = population[best2];
}

// função para realizar o cruzamento entre os pais
void crossover(struct chromosome* parents, struct chromosome* offspring) {
    int point = rand() % NUM_CITIES;
    // copiar as primeiras cidades do primeiro pai
    for (int i = 0; i < point; i++) {
        offspring[0].cities[i] = parents[0].cities[i];
        offspring[1].cities[i] = parents[1].cities[i];
    }
    pass
  }
