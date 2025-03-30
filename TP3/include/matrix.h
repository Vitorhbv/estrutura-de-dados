#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para uma matriz 2x2.
typedef struct {
    long long int mat[2][2];
} Matrix2x2;

// Inicializa uma matriz 2x2.
void initMatrix(Matrix2x2 *matrix);

// Multiplica duas matrizes 2x2.
void multiplyMatrices(Matrix2x2 *result, const Matrix2x2 *a, const Matrix2x2 *b);

//função para imprimir a matriz 2x2
void printMatrix(const Matrix2x2 *matrix);

//libera a memória alocada para a matriz 2x2
//void destroyMatrix(Matrix2x2 *matrix);

#endif /* MATRIX_H */
