/* ================================================================
   Menor Caminho em Grafo Não Direcionado e Ponderado
   Júlia Paz, Lucas Montimór, Miguel Zschornack
   ================================================================ */

#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF INT_MAX


/* ---------------------------------------------------------------
   Retorna o índice do vértice com a menor distância que ainda
   não foi visitado. Se nenhum estiver disponível, retorna -1.
   --------------------------------------------------------------- */
int obterVerticeComMenorDistancia(int distancia[], int visitado[], int totalVertices) {
    int menorValor = INF;
    int indiceMenor = -1;
    int i;

    for (i = 0; i < totalVertices; i++) {
        if (!visitado[i] && distancia[i] < menorValor) {
            menorValor = distancia[i];
            indiceMenor = i;
        }
    }
    return indiceMenor;
}


/* ---------------------------------------------------------------
   Imprime recursivamente o caminho da origem até o vértice 'atual'
   usando o vetor de pais.
   --------------------------------------------------------------- */
void imprimirCaminho(int pai[], int atual) {
    if (atual == -1) {
        return;
    }

    if (pai[atual] == -1) { /* chegou na origem */
        printf("%d", atual + 1);
        return;
    }

    imprimirCaminho(pai, pai[atual]);
    printf(" -> %d", atual + 1);
}


/* ---------------------------------------------------------------
   Algoritmo de Dijkstra
   --------------------------------------------------------------- */
void dijkstra(int grafo[MAX][MAX], int totalVertices, int origem, int destino) {
    int distancia[MAX];
    int visitado[MAX];
    int pai[MAX];
    int i, j;

    /* Inicialização */
    for (i = 0; i < totalVertices; i++) {
        distancia[i] = INF;
        visitado[i] = 0;
        pai[i] = -1;
    }

    distancia[origem] = 0;

    /* Processamento principal */
    for (i = 0; i < totalVertices - 1; i++) {
        int verticeAtual = obterVerticeComMenorDistancia(distancia, visitado, totalVertices);

        if (verticeAtual == -1) {
            break;
        }

        visitado[verticeAtual] = 1;

        for (j = 0; j < totalVertices; j++) {
            /* Verifica possibilidade de relaxamento */
            if (!visitado[j] &&
                grafo[verticeAtual][j] != 0 &&
                distancia[verticeAtual] != INF) {

                int novaDistancia = distancia[verticeAtual] + grafo[verticeAtual][j];

                if (novaDistancia < distancia[j]) {
                    distancia[j] = novaDistancia;
                    pai[j] = verticeAtual;
                }
            }
        }
    }

    /* Resultado final */
    printf("\n===== RESULTADO =====\n");

    if (distancia[destino] == INF) {
        printf("Nao existe caminho entre %d e %d.\n", origem + 1, destino + 1);
    } else {
        printf("Menor custo: %d\n", distancia[destino]);
        printf("Caminho: ");
        imprimirCaminho(pai, destino);
        printf("\n");
    }
}


/* ---------------------------------------------------------------
   Função Principal
   --------------------------------------------------------------- */
int main(void) {
    int totalVertices, totalArestas;
    int grafo[MAX][MAX];
    int i, j;
    int verticeA, verticeB, peso;
    int origem, destino;

    /* Inicializa matriz de adjacência */
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            grafo[i][j] = 0;
        }
    }

    printf("Numero de vertices (1 a 10): ");
    scanf("%d", &totalVertices);

    if (totalVertices < 1 || totalVertices > MAX) {
        printf("Erro! numero invalido de vertices.\n");
        return 1;
    }

    printf("Numero de arestas: ");
    scanf("%d", &totalArestas);

    if (totalArestas < 0) {
        printf("Erro! numero invalido de arestas.\n");
        return 1;
    }

    printf("\nInforme cada aresta no formato: verticeA verticeB peso\n");
    printf("(vertices de 1 a %d)\n\n", totalVertices);

    for (i = 0; i < totalArestas; i++) {
        scanf("%d %d %d", &verticeA, &verticeB, &peso);

        if (verticeA < 1 || verticeA > totalVertices ||
            verticeB < 1 || verticeB > totalVertices ||
            peso < 0) {

            printf("Aresta invalida: %d %d %d\n", verticeA, verticeB, peso);
            return 1;
        }

        grafo[verticeA - 1][verticeB - 1] = peso;
        grafo[verticeB - 1][verticeA - 1] = peso;
    }

    printf("\nVertice de origem (1..%d): ", totalVertices);
    scanf("%d", &origem);

    printf("Vertice de destino (1..%d): ", totalVertices);
    scanf("%d", &destino);

    if (origem < 1 || origem > totalVertices ||
        destino < 1 || destino > totalVertices) {
        printf("Erro: vertices invalidos.\n");
        return 1;
    }

    dijkstra(grafo, totalVertices, origem - 1, destino - 1);

    return 0;
}
