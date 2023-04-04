class Aresta: 
    def __init__(self, origem, destino, cor):
        self.origem = origem
        self.destino = destino
        self.cor = cor

def obterTrilhaEulerianaAlternante(arestas, n):
    grau = [0 for i in range(n)] # lista para armazenar o grau de cada vértice, sendo possível descartar logo no início se o grau de algum vértice for ímpar
    adj = [[] for i in range(n)] # lista de adjacências
    cores = [[-1 for j in range(n)] for i in range(n)] # matriz para armazenar a cor de cada aresta

    for aresta in arestas:
        grau[aresta.origem] += 1
        grau[aresta.destino] += 1
        adj[aresta.origem].append(aresta.destino)
        adj[aresta.destino].append(aresta.origem)
        cores[aresta.origem][aresta.destino] = aresta.cor
        cores[aresta.destino][aresta.origem] = aresta.cor

    for i in range(n):
        if (grau[i] % 2 != 0): # se o grau de algum vértice for ímpar, não é possível montar uma trilha Euleriana
            return []

    pilha = [0] # pilha para armazenar os vértices visitados
    trilha = []
    coresUltimasArestas = [-1] # cor alternante para permitir o uso da primeira aresta com qualquer cor

    while (len(pilha) > 0):
        v = pilha[-1]

        for u in adj[v]:
            if cores[v][u] != coresUltimasArestas[-1]: # se a cor da aresta for diferente da cor da última aresta adicionada na trilha, podemos adicionar a aresta
                adj[v].remove(u)
                adj[u].remove(v)

                grau[v] -= 1
                grau[u] -= 1

                pilha.append(u)
                coresUltimasArestas.append(cores[v][u])

                break
        else:
            coresUltimasArestas.pop()
            vertice = pilha.pop()

            if (grau[vertice] % 2 != 0): # se o grau de algum vértice for ímpar, não é possível montar uma trilha Euleriana alternante
                return []
            
            trilha.append(vertice)

    if len(trilha) < len(arestas) + 1: # se a trilha não tiver o mesmo número de arestas que o grafo, não é possível montar uma trilha Euleriana alternante
        return []

    return trilha

def main():
    arestas = []
    n, m = map(int, input().split())

    for i in range(m):
        u, v, c = map(int, input().split())
        arestas.append(Aresta(u, v, c))

    trilha = obterTrilhaEulerianaAlternante(arestas, n)

    if (trilha == []):
        print('Não possui trilha Euleriana alternante')
    else:
        print(*trilha)

main()