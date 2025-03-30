#include <iostream>
#include "../include/unionFind.hpp"
#include "../include/heap.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    Aresta* arestas = new Aresta[m];

    for (int i = 0; i < m; i++) {
        int u, v, c;
        std::cin >> u >> v >> c;
        arestas[i] = Aresta{u, v, c};
    }

    UnionFind uf(n);
    Heap heap(m); 

    for (int i = 0; i < m; i++) {
        heap.Inserir(i); 
    }

    int arvoreGeradoraMinima = 0;

    while (!heap.Vazio()) {
        int menorArestaIndice = heap.Remover();
        int u = arestas[menorArestaIndice].u;
        int v = arestas[menorArestaIndice].v;

        if (uf.Find(u) != uf.Find(v)) {
            arvoreGeradoraMinima += arestas[menorArestaIndice].custo;
            uf.Union(u, v);
        }
    }

    std::cout << arvoreGeradoraMinima << std::endl;

    delete[] arestas;

    return 0;
}
