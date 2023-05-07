class Conexao:
    def __init__(self, origem, destino, custo):
        self.origem = origem
        self.destino = destino
        self.custo = custo

def find_set(pai, i):
    if pai[i] == i:
        return i
    
    return find_set(pai, pai[i])

def union(pai, rank, x, y):
    raiz_x = find_set(pai, x)
    raiz_y = find_set(pai, y)

    if rank[raiz_x] < rank[raiz_y]:
        pai[raiz_x] = raiz_y
    elif rank[raiz_x] > rank[raiz_y]:
        pai[raiz_y] = raiz_x
    else:
        pai[raiz_y] = raiz_x
        rank[raiz_x] += 1

def kruskal(conexoes, k):
    vertices = obterVertices(conexoes)

    resultado = []
    indice_conexao = 0
    indice_ordenado = 0

    conexoes_ordenadas = sorted(conexoes, key=lambda conexao: conexao.custo)

    pai = {}
    rank = {}

    for vertice in vertices:
        pai[vertice] = vertice
        rank[vertice] = 0

    while indice_ordenado < len(vertices) - k:
        conexao = conexoes_ordenadas[indice_conexao]
        indice_conexao += 1

        origem_raiz = find_set(pai, conexao.origem)
        destino_raiz = find_set(pai, conexao.destino)

        if origem_raiz != destino_raiz:
            resultado.append(conexao)
            indice_ordenado += 1
            union(pai, rank, origem_raiz, destino_raiz)

    return resultado
    
def obterVertices(conexoes):
    vertices = set()

    for conexao in conexoes:
        vertices.add(conexao.origem)
        vertices.add(conexao.destino)

    return vertices

def obterCustoTotal(resultado):
    custoTotal = 0

    for conexao in resultado:
        custoTotal += conexao.custo

    return custoTotal

def main():
    conexoes = []
    n, m, k = map(int, input().split())

    for i in range(m):
        a, b, w = map(int, input().split())
        conexoes.append(Conexao(a, b, w))

    resultado = kruskal(conexoes, k)

    print(obterCustoTotal(resultado))

main()