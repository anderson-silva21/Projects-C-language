#include <stdio.h>
#include <stdlib.h>

#define N 3

void printMatrix(double mat[N][N])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%.2lf ", mat[i][j]);
        printf("\n");
    }
}

void GaussJordan(double mat[N][N], double inv[N][N])
{
    int i, j, k;
    double pivot, temp;

    // Cria a matriz identidade para a matriz inversa
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            inv[i][j] = (i == j) ? 1 : 0;

    // Eliminação de Gauss-Jordan
    for (i = 0; i < N; i++)
    {
        pivot = mat[i][i];
        for (j = 0; j < N; j++)
        {
            mat[i][j] /= pivot;
            inv[i][j] /= pivot;
        }
        for (j = 0; j < N; j++)
        {
            if (i != j)
            {
                temp = mat[j][i];
                for (k = 0; k < N; k++)
                {
                    mat[j][k] -= mat[i][k] * temp;
                    inv[j][k] -= inv[i][k] * temp;
                }
            }
        }
    }
}

int main()
{
    double mat[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double inv[N][N];
    GaussJordan(mat, inv);
    printf("Matriz original:\n");
    printMatrix(mat);
    printf("\nMatriz inversa:\n");
    printMatrix(inv);
    return 0;
}
