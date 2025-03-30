#ifndef SEG_TREE_H
#define SEG_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

// Estrutura da árvore de segmentos.
typedef struct {
    int size;           // Tamanho da segtree.
    Matrix2x2 *tree;    // Array de matrizes para armazenar os nós da segtree.
} SegTree;

// Funções para a árvore de segmentos.

// Inicializa e constrói a árvore de segmentos.
void initSegTree(SegTree *segtree, int size);

// Atualiza um nó da árvore de segmentos.
void updateSegTree(SegTree *segtree, int node, int start, int end, int idx, const Matrix2x2 *val);

// Consulta na árvore de segmentos.
void querySegTree(Matrix2x2 *result, SegTree *segtree, int node, int start, int end, int l, int r);

// Libera a memória alocada para a árvore de segmentos.
void freeSegTree(SegTree *segtree);

#endif /* SEG_TREE_H */
