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

    for (int i = 0; i < totalVertices; i++) {
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
    if (atual == -1)
        return;

    if (pai[atual] == -1) { /* chegou na origem */
        printf("%c", atual + 'A');
        return;
    }

    imprimirCaminho(pai, pai[atual]);
    printf(" -> %c", atual + 'A');
}

/* ---------------------------------------------------------------
   Algoritmo de Dijkstra
   --------------------------------------------------------------- */

void dijkstra(int grafo[MAX][MAX], int totalVertices, int origem, int destino) {
    int distancia[MAX], visitado[MAX], pai[MAX];

    /* Inicialização */
    for (int i = 0; i < totalVertices; i++) {
        distancia[i] = INF;
        visitado[i] = 0;
        pai[i] = -1;
    }

    distancia[origem] = 0;

    /* Processamento principal */
    for (int i = 0; i < totalVertices - 1; i++) {
        int atual = obterVerticeComMenorDistancia(distancia, visitado, totalVertices);
        if (atual == -1) break;

        visitado[atual] = 1;

        for (int j = 0; j < totalVertices; j++) {
            /* Verifica possibilidade de relaxamento */
            if (!visitado[j] &&
                grafo[atual][j] != 0 &&
                distancia[atual] != INF) {

                int novaDist = distancia[atual] + grafo[atual][j];

                if (novaDist < distancia[j]) {
                    distancia[j] = novaDist;
                    pai[j] = atual;
                }
            }
        }
    }

    /* Resultado final */
    
    printf("\n===== RESULTADO =====\n");

    if (distancia[destino] == INF) {
        printf("Nao existe caminho entre %c e %c.\n", origem + 'A', destino + 'A');
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
    int grafo[MAX][MAX] = {0};

    printf("Numero de vertices (A..J): ");
    scanf("%d", &totalVertices);

    if (totalVertices < 1 || totalVertices > MAX) {
        printf("Erro! numero invalido.\n");
        return 1;
    }

    printf("Numero de arestas: ");
    scanf("%d", &totalArestas);

    printf("\nInforme cada aresta como: A B peso\n\n");

    for (int i = 0; i < totalArestas; i++) {
        char a, b;
        int peso;
        scanf(" %c %c %d", &a, &b, &peso);

        int vA = a - 'A';
        int vB = b - 'A';

        grafo[vA][vB] = peso;
        grafo[vB][vA] = peso;
    }

    char origChar, destChar;

    printf("\nVertice de origem (A..%c): ", 'A' + totalVertices - 1);
    scanf(" %c", &origChar);

    printf("Vertice de destino (A..%c): ", 'A' + totalVertices - 1);
    scanf(" %c", &destChar);

    int origem = origChar - 'A';
    int destino = destChar - 'A';

    dijkstra(grafo, totalVertices, origem, destino);

    return 0;
}