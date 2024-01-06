#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printVector(double* vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.4f\t", vector[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of equations and unknowns (n): ");
    scanf("%d", &n);

    double** A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
    }
    double* b = (double*)malloc(n * sizeof(double));

    printf("Enter the coefficients of matrix A and vector b:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
        printf("b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    double epsilon;
    printf("Enter the parameter for accuracy (epsilon): ");
    scanf("%lf", &epsilon);

    double* x = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    int maxIterations;
    printf("Enter the maximum number of iterations: ");
    scanf("%d", &maxIterations);

    int iterations = 0;
    double prop = 0.0;
    while (iterations < maxIterations) {
        double* xNew = (double*)malloc(n * sizeof(double));
        double maxDelta = 0.0; // Maximum value of deltai

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            xNew[i] = (b[i] - sum) / A[i][i];

            double deltai = fabs(xNew[i] - x[i]);
            if (deltai > maxDelta) {
                maxDelta = deltai;
            }
        }

        prop = maxDelta;

        if (prop < epsilon) {
            printf("Solution found with the specified accuracy:\n");
            printVector(xNew, n);
            break;
        }

        for (int i = 0; i < n; i++) {
            x[i] = xNew[i];
        }

        free(xNew);
        iterations++;
    }

    if (iterations >= maxIterations) {
        printf("Maximum number of iterations reached without finding a solution.\n");
    }

    // Output the value of the parameter prop
    printf("Parameter prop: %.6f\n", prop);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    return 0;
}
