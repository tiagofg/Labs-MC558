class Aresta:
    def __init__(self, origem, destino, energia):
        self.origem = origem
        self.destino = destino
        self.energia = energia
        
    def __str__(self):
        return f'({self.origem}, {self.destino}, {self.energia})'

def possivelBaterOJogo(arestas, n):
    dist = [float('-inf') for _ in range(n)]
    dist[0] = 100

    for _ in range(n):
        for aresta in arestas:
            if dist[aresta.origem] + aresta.energia > dist[aresta.destino] and dist[aresta.origem] + aresta.energia > 0:
                dist[aresta.destino] = dist[aresta.origem] + aresta.energia

    if dist[n - 1] <= 0:
        return "impossible"

    return "possible"

def main():
    n = int(input())
    w = [int(x) for x in input().split()]
    m = int(input())

    arestas = []
    for _ in range(m):
        u, v = map(int, input().split())
        arestas.append(Aresta(u, v, w[v]))

    print(possivelBaterOJogo(arestas, n))

main()