#include "../include/matrix.h"
#include "../include/segtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    SegTree segtree;
    initSegTree(&segtree, n);
    double soma = 0;
    for (int i = 0; i < q; i++) {
        char op;
        scanf(" %c", &op);

        if (op == 'u') {
            double start = clock();
            int idx;
            Matrix2x2 mat;
            scanf("%d", &idx);
            scanf("%lld %lld", &mat.mat[0][0], &mat.mat[0][1]);
            scanf("%lld %lld", &mat.mat[1][0], &mat.mat[1][1]);

            updateSegTree(&segtree, 1, 0, n - 1, idx, &mat);

            double end = clock();
            soma += (end - start);
        } else if (op == 'q') {
            int t0, td, x, y;
            scanf("%d %d %d %d", &t0, &td, &x, &y);

            Matrix2x2 result;
            querySegTree(&result, &segtree, 1, 0, n - 1, t0, td);

            long long int finalX = result.mat[0][0] * x + result.mat[0][1] * y;
            long long int finalY = result.mat[1][0] * x + result.mat[1][1] * y;
            //printf("%lld %lld\n", finalX % 100000000, finalY % 100000000);
            
        }
    }
    printf("Time: %lf\n", soma / CLOCKS_PER_SEC);
    freeSegTree(&segtree);
    return 0;
}

