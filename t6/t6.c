#include "shortest_path.h"

int main(void) {
    Grafo *g = novoGrafo(4);
    adicionaArco(g, 0, 1, 2);
    adicionaArco(g, 0, 2, 1);
    adicionaArco(g, 1, 3, 3);
    adicionaArco(g, 2, 3, 6);

    printf("Grafo gerado:\n");
    printGrafo(g);

    int *dist = caminhoMinimo(g, 0, 3);
    printf("Distância mínima entre 0 e 3: %d\n", dist[3]);
    free(dist);
    destroiGrafo(g);

    return 0;
}
