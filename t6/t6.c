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
    FILE* arquivo = fopen(argv[1], "r");

    int n, Q;
    fscanf(arquivo, "%d %d", &n, &Q);

    Moeda* moedas = (Moeda*) malloc(n * sizeof(Moeda));
    for (int i = 0; i < n; i++) {
        int valor, peso, qtde;
        fscanf(arquivo, "%d %d %d", &valor, &peso, &qtde);
        moedas[i] = (Moeda) {valor, peso, qtde};
    }

    int numVertices = 2 + n * (Q + 1);
    Grafo* g = criarGrafo(moedas, n, numVertices, Q);
    fclose(arquivo);

    int* dist = caminhoMinimo(g, 0, numVertices - 1);
    int pesoMinimo = dist[numVertices - 1];

    if (pesoMinimo != INT_MAX) {
        printf("%d\n", pesoMinimo);
    } else {
        int maiorValor = 0;
        int pesoMinimoMaiorValor = INT_MAX;

        for (int i = 0; i <= Q; i++) {
            for (int j = Q - i; j < numVertices - 3 - i; j = j + Q + 1) {
                if (Q - i - 1 < maiorValor) {
                    break;
                }

                if (dist[j] < pesoMinimoMaiorValor) {
                    maiorValor = Q - i - 1;
                    pesoMinimoMaiorValor = dist[j];
                }
            }
        }

        printf("%d %d\n", maiorValor, pesoMinimoMaiorValor);
    }

    destroiGrafo(g);
    free(moedas);
    free(dist);

    return 0;
}