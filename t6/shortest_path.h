#ifndef PATH_H
#define PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct arco { // nó da lista de adjacências
    int u, v, peso;
    struct arco *proximo;
} Arco;

typedef struct {
    int n; // número de nós
    int m; // tamanho do vetor de listas de adjacências
    Arco **arcos; // vetor de lista de adjacências
} Grafo;

/* cria um novo grafo vazio */
Grafo *novoGrafoVazio();

/* cria um novo grafo com n vértices */
Grafo *novoGrafo(int n);

/* destruidor */
void destroiGrafo(Grafo *g);

/* adiciona um vértice ao grafo
 * devolve o índice do novo vértice */
int adicionaVertice(Grafo *g);

/* adiciona um arco de u a v com peso w
   0 <= u, v <= n-1  */
void adicionaArco(Grafo *g, int u, int v, int w);

/* número de arcos do grafo */
int numArcos(Grafo *g);

/* para facilitar seu debug */
void printGrafo(Grafo *g);

/* calcula um caminho mínimo de s a t num grafo sem ciclos orientados
 * devolve o custo de um caminho mínimo */
int *caminhoMinimo(Grafo *g, int s, int t);

#endif // PATH_H
