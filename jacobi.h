#include<iostream>
#include<cmath>
#include "Equations.h"
#include "MultiMatrix.h"

#define EPSILON 0.01

float* jacobi(float** A, float* y, int n) {
    int i, j, it;
    float** B;
    double* R = new float[n];
    float* R1 = new float[n];

    float ri, r0, sumi, sum0;

    B = new float*[n];
        for (int i = 0; i < n; i++)
            B[i] = new float[n];

    float* g = new float[n];
    float* x = new float[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {   
            B[i][j] = i == j ? 0 : -A[i][j]/A[i][i];

        g[i] = y[i]/A[i][i]; 
        }
    }

    for (i = 0; i < n; i++) {
        sum0 += y[i] * y[i];
    }

    r0 = sqrt(sum0);

    float* xnew = new float[n];

    for (i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    int iter = 0;

    for (it = 0; it < 30; it++) {
        for (i = 0; i < n; i++) {
            xnew[i] = 0.0;
            for (j = 0; j < n; j++) {
                xnew[i] += B[i][j] * x[j];
            }
        }

        for (i = 0; i < n; i++) {
            x[i] = xnew[i] + g[i];
        }

        R = multiMatrix(A, y, n);

        for (i = 0; i < n; i++) {
            R1[i] = R[i] - y[i];
            sumi += R1[i] * R1[i];
        }

        ri = sqrt(sumi);

        // ri = 1;

        // iter++;
        // if (r0/ri <= EPSILON)
        //     break;
    }

    // cout << "Number Iteration: " << iter << endl;
    // cout << r0 / ri << endl;

    return x;
}