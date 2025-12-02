/* ================================================================
   Menor Caminho em Grafo Não Direcionado e Ponderado
   AUTORES: Júlia Paz, Lucas Montimór, Miguel Zschornack
   LINGUAGEM: C ANSI (compatível com C89/C90)

   OBS:
       --> O programa usa lista de arestas para entrada, pq é mais intuitivo.
       --> O grafo é armazenado em matriz de adjacência.
       --> Os vértices são digitados de 1 a n, mas internamente convertidos para 0..n-1.

   ================================================================ */

#include <stdio.h>
#include <limits.h>

#define MAX 10        /* número máximo de vértices */
#define INF INT_MAX   /* representação de infinito */


int minDistance(int dist[], int visited[], int n) { // Retorna o índice do vértice com a menor distância ainda não visitado. Ou -1 se nenhum disponível.
    int min = INF;
    int min_index = -1;
    int i;

    for (i = 0; i < n; i++) {
        /* só considera vértices não visitados */
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) { // Imprime recursivamente o caminho do vértice origem até j, usando o vetor parent[] montado pelo algoritmo Dijkstra. A impressão é feita em notação 1-based (vértices iniciam em 1).
    if (j == -1) return; /* caso base */

    /* se não tem pai, j é a origem */
    if (parent[j] == -1) {
        printf("%d", j + 1); /* (+1) para imprimir 1-based */
        return;
    }

    /* volta recursivamente até a origem */
    printPath(parent, parent[j]);

    /* imprime o vértice atual */
    printf(" -> %d", j + 1);
}

/* ----------------------------------------------------------------
   função dijkstra
   objetivo: Aplicar o algoritmo de Dijkstra para encontrar o menor caminho entre src e dest no grafo dado, onde:
       graph[][] -> matriz de adjacência do grafo
       n -> número de vértices
       src -> vértice de origem (0-based)
       dest -> vértice de destino (0-based)
   ---------------------------------------------------------------- */
void dijkstra(int graph[MAX][MAX], int n, int src, int dest) {
    int dist[MAX];     /* distancia mínima encontrada até cada vértice */
    int visited[MAX];  /* marca quais vértices já foram processados */
    int parent[MAX];   /* guarda o pai de cada vértice no caminho */
    int i, j;

    /* inicialização dos vetores internos */
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1; /* -1 indica que não há pai ainda */
    }

    /* a distância do vértice de origem é sempre 0 */
    dist[src] = 0;

    /* executa n-1 vezes (funcionamento padrão do Dijkstra) */
    for (i = 0; i < n - 1; i++) {

        /* escolhe o vértice mais próximo ainda não visitado */
        int u = minDistance(dist, visited, n);

        if (u == -1) {
            /* sem vértices acessíveis restantes */
            break;
        }

        visited[u] = 1;

        /* atualiza as distâncias dos vértices vizinhos */
        for (j = 0; j < n; j++) {

            /* condições para relaxamento:
               - j ainda não foi visitado
               - existe aresta entre u e j (graph[u][j] != 0)
               - a distância de u não é infinita
               - melhorar dist[j] é possível
            */
            if (!visited[j] && graph[u][j] != 0 && dist[u] != INF) {
                int novaDist = dist[u] + graph[u][j];

                if (novaDist < dist[j]) {
                    dist[j] = novaDist;
                    parent[j] = u; /* registra o caminho */
                }
            }
        }
    }

    /* exibe o resultado final */
    printf("\n===== RESULTADO =====\n");

    if (dist[dest] == INF) {
        printf("Nao existe caminho entre %d e %d.\n",
               src + 1, dest + 1);
    } else {
        printf("Menor custo: %d\n", dist[dest]);
        printf("Caminho: ");
        printPath(parent, dest);
        printf("\n");
    }
}

/* ----------------------------------------------------------------
   função principal
   ---------------------------------------------------------------- */
int main(void) {
    int n, m;
    int graph[MAX][MAX];
    int i, j;
    int u, v, w;
    int src, dest;

    /* inicializa toda matriz com 0 (sem arestas) */
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }

    /* entrada: número de vértices */
    printf("Numero de vertices (1 a 10): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Erro! numero invalido de vertices.\n");
        return 1;
    }

    /* entrada: número de arestas */
    printf("Numero de arestas: ");
    scanf("%d", &m);

    if (m < 0) {
        printf("Erro! numero invalido de arestas.\n");
        return 1;
    }

    /* entrada das arestas */
    printf("\nInforme cada aresta no formato: u v peso\n");
    printf("(vertices de 1 a %d)\n\n", n);

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);

        /* validação da aresta */
        if (u < 1 || u > n || v < 1 || v > n || w < 0) {
            printf("Aresta invalida: %d %d %d\n", u, v, w);
            return 1;
        }

        /* grafo não direcionado */
        graph[u - 1][v - 1] = w;
        graph[v - 1][u - 1] = w;
    }

    /* entrada da origem e destino */
    printf("\nVertice de origem (1..%d): ", n);
    scanf("%d", &src);

    printf("Vertice de destino (1..%d): ", n);
    scanf("%d", &dest);

    if (src < 1 || src > n || dest < 1 || dest > n) {
        printf("Erro: vertices invalidos.\n");
        return 1;
    }

    /* chama o algoritmo de dijkstra */
    dijkstra(graph, n, src - 1, dest - 1);

    return 0;
}