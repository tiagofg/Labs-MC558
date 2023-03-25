class Vertice: 
    def __init__(self, num, grau):
        self.num = num
        self.grau = grau
        
def rotularVertices(d, n):
    vertices = []

    for i in range(n):
        vertices.append(Vertice(i, d[i])) #adicionando identificações para os vértices para não serem perdidos após ordenar a sequência

    return vertices

def ehSequenciaGrafica(d, n):
    adj = [[] for i in range(n)]
    i = 0

    vertices = rotularVertices(d, n)

    while (i < n):
        d1 = vertices[0].grau
        v1 = vertices[0].num
        vertices = vertices[1 : n]

        if (d1 > len(vertices)): #se o grau do primeiro vértice for maior que o resto da sequência sabemos que é impossível montar um grafo
            return []

        for j in range(d1):
            vertices[j].grau -= 1

            if (vertices[j].grau < 0): #caso a sequência tenha dado algum grau negativo sabemos que é impossível montar um grafo
                return []

            #adicionando ambos os vértices nas respectivas listas de adjacências
            adj[v1].append(vertices[j].num + 1)
            adj[vertices[j].num].append(v1 + 1)

        vertices.sort(key=lambda x: x.grau, reverse=True)

        i += 1
    
    return adj

def printListaAdj(lista):
    for i in range(len(lista)):
        lista[i].sort()
        print(*lista[i])
    
def main():
    n = int(input())
    d = [int(x) for x in input().split()]

    listaAdj = ehSequenciaGrafica(d, n)

    if (listaAdj == []):
        print('Não é sequência gráfica!')
    else:
        printListaAdj(listaAdj)

main()
