#include<iostream>
#include<fstream>
#include<iomanip>

#ifndef MATRIX_F_NEW
#define MATRIX_F_NEW

#include "MatrixF.h"

using namespace std;

// Return matrix F
double* matrixFNew(int sizeMatrix, double topBoundary, double rightBoundary) {
	ofstream outfile ("matrixFNew.dat");

	int size = sizeMatrix + 2;
	int sizeF = sizeMatrix * sizeMatrix;

	double delta_h = topBoundary / (size - 1);

	int** matrix = new int*[sizeMatrix];
        for (int i = 0; i < sizeMatrix; i++)
                matrix[i] = new int[sizeMatrix];

	double* matrix_F = matrixF(sizeMatrix, topBoundary, rightBoundary);

	double* matrix_FNew = new double[sizeF];

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
				matrix_FNew[n1 - 1] = matrix_F[matrix[i][j]];
			}
		}
	}

	for (int j = 0; j < sizeMatrix; j++) {
		for (int i = sizeMatrix - 1; i >= 0; i--) {
			if (i < x0) {
				n2++;
				matrix_FNew[n1 + n2 - 1] = matrix_F[matrix[i][j]];
			}
		}
	}

	for (int j = 0; j < sizeMatrix; j++) {
		for (int i = sizeMatrix - 1; i >= 0; i--) {
			if (i == x0) {
				n3++;
				matrix_FNew[n1 + n2 + n3 - 1] = matrix_F[matrix[i][j]];
			}
		}
	}

	// Show n1, n2, n3
	outfile << "n1 = " << n1;
	outfile << endl;
	outfile << "n2 = " << n2;
	outfile << endl;
	outfile << "n3 = " << n3;
	outfile << endl;
	outfile << endl;

	// Show matrix F New
	for (int i = 0; i < sizeF; i++) {
		outfile << setw(10) << matrix_FNew[i] << endl;
	}

	outfile.close();

	return (matrix_FNew);
}

#endif