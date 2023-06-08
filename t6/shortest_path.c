#include "shortest_path.h"

/* A lista de adjacências cresce exponencialmente -- amortizado constante */
#define TAMANHO_INICIAL 1024

// Grafo: -------------------------------------------------------------------------------
void aumentaVetor(Grafo *g, int n) {
    if (g->m >= n) return;
    while (g->m < n)
        g->m *= 2;
    g->arcos = (Arco **) realloc(g->arcos, g->m * sizeof(Arco *));
}

Grafo *novoGrafoVazio() {
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    g->n = 0;
    g->m = TAMANHO_INICIAL;
    g->arcos = (Arco **) calloc(TAMANHO_INICIAL, sizeof(Arco *));
    return g;
}

Grafo *novoGrafo(int n) {
    Grafo *g;
    g = novoGrafoVazio();
    aumentaVetor(g, n);
    g->n = n;
    memset(g->arcos, 0, g->m * sizeof(Arco *));
    return g;
}

void destroiLista(Arco *head) {
    if (head != NULL) {
        destroiLista(head->proximo);
        free(head);
    }
}

void destroiGrafo(Grafo *g) {
    for (int i = 0; i < g->n; i++)
        destroiLista(g->arcos[i]);
    free(g->arcos);
    free(g);
}

int adicionaVertice(Grafo *g) {
    g->n++;
    aumentaVetor(g, g->n);
    g->arcos[g->n - 1] = NULL;
    return g->n - 1;
}

void adicionaArco(Grafo *g, int u, int v, int w) {
    Arco *e = (Arco *) malloc(sizeof(Arco));
    e->u = u;
    e->v = v;
    e->peso = w;
    e->proximo = g->arcos[u];
    g->arcos[u] = e;
}

int numArcos(Grafo *g) {
    int ret = 0;
    for (int i = 0; i < g->n; i++)
        for (Arco *e = g->arcos[i]; e != NULL; e = e->proximo, ret++);
    return ret;
}

void printGrafo(Grafo *g) {
    printf("# vértices: %d\n", g->n);
    for (int i = 0; i < g->n; i++) {
        printf("%d: ", i);
        for (Arco *e = g->arcos[i]; e != NULL; e = e->proximo)
            printf("(%d, %d, %d) ", e->u, e->v, e->peso);
        printf("\n");
    }
}

// Caminho Mínimo: ----------------------------------------------------------------------
void _ordTop(Grafo *g, int u, short visitado[], int pilha[], int *topo) {
    visitado[u] = 1;
    for (Arco *e = g->arcos[u]; e != NULL; e = e->proximo)
        if (!visitado[e->v])
            _ordTop(g, e->v, visitado, pilha, topo);
    pilha[++(*topo)] = u;
}

void ordTop(Grafo *g, int pilha[]) {
    int topo = -1;
    short *visitado = (short *) calloc(g->n, sizeof(short));
    for (int i = 0; i < g->n; i++)
        if (!visitado[i])
            _ordTop(g, i, visitado, pilha, &topo);
    free(visitado);
}

int *caminhoMinimo(Grafo *g, int s, int t) {
    int *pilha = (int *) malloc(g->n * sizeof(int));
    int *dist = (int *) malloc(g->n * sizeof(int));
    ordTop(g, pilha);

    // Inicializa as distâncias:
    for (int i = 0; i < g->n; i++)
        dist[i] = INT_MAX;
    dist[s] = 0;

    // Calcula as distâncias usando programação dinâmica:
    int topo = g->n;
    while (topo > 0) {
        int u = pilha[--topo];
        if (dist[u] != INT_MAX)
            for (Arco *e = g->arcos[u]; e != NULL; e = e->proximo)
                if (dist[u] + e->peso < dist[e->v])
                    dist[e->v] = dist[u] + e->peso;
    }

    free(pilha);
    return dist;
}
