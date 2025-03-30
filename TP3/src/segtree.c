#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/segtree.h"
#include "../include/matrix.h"


void initSegTree(SegTree *segtree, int size) {
    segtree->size = size;
    segtree->tree = (Matrix2x2 *)malloc(sizeof(Matrix2x2) * size * 4);

    if (segtree->tree == NULL) {
        fprintf(stderr, "Falha na alocação de memória para a árvore de segmentos.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size * 4; i++) {
        initMatrix(&segtree->tree[i]);
    }
}

void updateSegTree(SegTree *segtree, int node, int start, int end, int idx, const Matrix2x2 *val) {
    if (start == end) {
        segtree->tree[node] = *val;
        return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid) {
        updateSegTree(segtree, 2 * node, start, mid, idx, val);
    } else {
        updateSegTree(segtree, 2 * node + 1, mid + 1, end, idx, val);
    }

    multiplyMatrices(&segtree->tree[node], &segtree->tree[2 * node], &segtree->tree[2 * node + 1]);
}


void querySegTree(Matrix2x2 *result, SegTree *segtree, int node, int start, int end, int l, int r) {
    if (r < start || l > end) {
        initMatrix(result);
        return;
    }

    if (l <= start && end <= r) {
        *result = segtree->tree[node];
        return;
    }

    int mid = (start + end) / 2;
    Matrix2x2 leftResult, rightResult;
    querySegTree(&leftResult, segtree, 2 * node, start, mid, l, r);
    querySegTree(&rightResult, segtree, 2 * node + 1, mid + 1, end, l, r);

    multiplyMatrices(result, &leftResult, &rightResult);
}

void freeSegTree(SegTree *segtree) {
    free(segtree->tree);
}

