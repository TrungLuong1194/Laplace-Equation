#include<iostream>
#include "Equations.h"

using namespace std;

double* jacobi(double **A, double* y, int n) {
    int i, j, it;
    double** B;
    
    B = new double*[n];
        for (int i = 0; i < n; i++)
                B[i] = new double[n];

    double* g = new double[n];
    double* x = new double[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = i == j ? 0 : -A[i][j]/A[i][i];

        g[i] = y[i]/A[i][i];
        }
    } 

    double* xnew = new double[n];

    for (i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    int iter = 50;

    for (it = 0; it < iter; it++) {

        for (i = 0; i < n; i++) {
            xnew[i] = 0.0;
            for (j = 0; j < n; j++) {
                xnew[i] += B[i][j] * x[j];
            }
        }

        for (i = 0; i < n; i++) {
            x[i] = xnew[i] + g[i];
        }

    }

    return x;
}