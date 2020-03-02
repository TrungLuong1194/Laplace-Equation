#include<iostream>
#include<fstream>
#include<iomanip>

#include "MatrixANew.h"
#include "MatrixFNew.h"
#include "LU.h"

using namespace std;

double* lu_transform(int sizeMatrix, double topBoundary, double rightBoundary) {

	int size = sizeMatrix * sizeMatrix;

	double** matrix_ANew = matrixANew(sizeMatrix, topBoundary, rightBoundary);

	double* matrix_FNew = matrixFNew(sizeMatrix, topBoundary, rightBoundary);

	double* matrix_U_LU;

	matrix_U_LU = luWithPivot(matrix_ANew, matrix_FNew, size);

	double delta_h = topBoundary / (sizeMatrix + 1);

	int** matrix = new int*[sizeMatrix];
        for (int i = 0; i < sizeMatrix; i++)
            matrix[i] = new int[sizeMatrix];

    double* matrixIndex = new double[size];

	// double x0 = (sizeMatrix / 2) * delta_h;
    int x0 = sizeMatrix / 2;

	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int count = 0;

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            matrix[i][j] = count;
            count++;
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i > x0) {
                n1++;
                matrixIndex[n1 - 1] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i < x0) {
                n2++;
                matrixIndex[n1 + n2 - 1] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i == x0) {
                n3++;
                matrixIndex[n1 + n2 + n3 - 1] = matrix[i][j];
            }
        }
    }

    // Matrix Original
    double* matrix_U_LU_Ori = new double[size];
    int index;

    for (int i = 0; i < size; i++) {
        index = matrixIndex[i];
        matrix_U_LU_Ori[index] = matrix_U_LU[i];
    }


    return (matrix_U_LU_Ori);
}