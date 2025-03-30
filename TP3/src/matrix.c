#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/matrix.h"

void  initMatrix(Matrix2x2 *matrix){
    matrix->mat[0][0] = 1;
    matrix->mat[0][1] = 0;
    matrix->mat[1][0] = 0;
    matrix->mat[1][1] = 1;
}

void multiplyMatrices(Matrix2x2 *result, const Matrix2x2 *a, const Matrix2x2 *b) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            long long sum = 0;
            for (int k = 0; k < 2; k++) {
                sum += (long long)a->mat[i][k] * b->mat[k][j];
            }
            result->mat[i][j] = sum % 100000000;
        }
    }
}


//void destroyMatrix(Matrix2x2* matrix){
    //free(matrix);
//}

void printMatrix(const Matrix2x2 *matrix) {
    printf("| %lld %lld |\n| %lld %lld |\n", matrix->mat[0][0], matrix->mat[0][1], matrix->mat[1][0], matrix->mat[1][1]);
}
