#include <stdio.h>
#include <stdlib.h>
#include "shortest_path.h"

typedef struct {
    int valor;
    int peso;
    int qtde;
} Moeda;

Grafo* criarGrafo(Moeda* moedas, int numMoedas, int numVertices, int troco) {
    Grafo* g = novoGrafo(numVertices);

    // Evitar alocar vértices que não serão atingíveis para economizar memória
    int* verticesAtingiveis = (int*) calloc(numVertices, sizeof(int));

    // Adiciona arcos da origem para as moedas
    for (int i = 0; i <= moedas[0].qtde; i++) {
        int v = (i * moedas[0].valor) + 1;

        if (v <= troco + 1) {
            adicionaArco(g, 0, v, i * moedas[0].peso);
            verticesAtingiveis[v] = 1;
        }
    }

    // Adiciona arcos das moedas para as moedas
    for (int k = 1; k < numMoedas; k++) {
        for (int i = 1 + ((k - 1) * (troco + 1)); i < k * (troco + 1); i++) {
            if (!verticesAtingiveis[i]) {
                continue;
            }
            
            for (int j = 0; j <= moedas[k].qtde; j++) {
                int v = troco + i + (j * moedas[k].valor) + 1;

                if (v <= (k + 1) * (troco + 1)) {
                    adicionaArco(g, i, v, j * moedas[k].peso);
                    verticesAtingiveis[v] = 1;
                }
            }
        }
    }

    free(verticesAtingiveis);

    // Adiciona arcos das moedas para o destino
    for (int i = troco + 1; i < numVertices; i = i + troco + 1) {
        adicionaArco(g, i, numVertices - 1, 0);
    }

    return g;
}

int main(int argc, char* argv[]) {
    int n, Q;
    scanf("%d %d", &n, &Q);

    Moeda* moedas = (Moeda*) malloc(n * sizeof(Moeda));
    for (int i = 0; i < n; i++) {
        int valor, peso, qtde;
        scanf("%d %d %d", &valor, &peso, &qtde);
        moedas[i] = (Moeda) {valor, peso, qtde};
    }

    int numVertices = 2 + n * (Q + 1);
    Grafo* g = criarGrafo(moedas, n, numVertices, Q);

    int* dist = caminhoMinimo(g, 0, numVertices - 1);
    int pesoMinimo = dist[numVertices - 1];

    if (pesoMinimo != INT_MAX) {
        printf("%d\n", pesoMinimo);
    } else {
        // Encontrar maior distância menor que o troco
        for (int i = numVertices - 1; i > 0; i--) {
            if (dist[i] != INT_MAX) {
                int maiorValor = i;

                // Encontrar o maior valor que pode ser formado e seja menor do que o troco
                while (maiorValor > Q) {
                    maiorValor = maiorValor - (Q + 1);
                }

                // Subtrair 1 porque o vértice 0 é a origem
                printf("%d %d\n", maiorValor - 1, dist[i]);

                break;
            }
        }
    }

    destroiGrafo(g);
    free(moedas);
    free(dist);

    return 0;
}