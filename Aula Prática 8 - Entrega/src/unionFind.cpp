#include "../include/unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    tamanho = quantidade_subconjuntos;
    subconjuntos = new Subconjunto[tamanho];
    for (int i = 0; i < tamanho; i++) {
        subconjuntos[i].representante = i;
        subconjuntos[i].rank = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

void UnionFind::Make(int x) {
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x) {
    if (subconjuntos[x].representante != x) {
        subconjuntos[x].representante = Find(subconjuntos[x].representante);
    }
    return subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y) {
    int xRaiz = Find(x);
    int yRaiz = Find(y);
    if (xRaiz == yRaiz) {
        return;
    }
    if (subconjuntos[xRaiz].rank < subconjuntos[yRaiz].rank) {
        subconjuntos[xRaiz].representante = yRaiz;
    } else if (subconjuntos[xRaiz].rank > subconjuntos[yRaiz].rank) {
        subconjuntos[yRaiz].representante = xRaiz;
    } else {
        subconjuntos[yRaiz].representante = xRaiz;
        subconjuntos[xRaiz].rank++;
    }
}