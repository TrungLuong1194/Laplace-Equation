#include<iostream>
#include<fstream>
#include<iomanip>

#include "Function.h"

using namespace std;

// Return matrix F
double* matrixF(int sizeMatrix, double topBoundary, double rightBoundary) {
	ofstream outfile1 ("matrixBoundary.dat");
	ofstream outfile2 ("matrixF.dat");

	int size = sizeMatrix + 2;

	double delta_h = topBoundary / (size - 1);

	double** matrix = new double*[size];
        for (int i = 0; i < size; i++)
                matrix[i] = new double[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}

	// create matrix boundary
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
				matrix[i][j] = funtionU1(j * delta_h, (size - 1 - i) * delta_h);
			}
		}

	}

	int sizeF = sizeMatrix * sizeMatrix;
	double* matrixF = new double[sizeF];
	int index = 0;

	// create matrix F
	for (int i = 1; i < size - 1; i++) {
		for (int j = 1; j < size - 1; j++) {
			matrixF[index] = delta_h * delta_h * funtionF(i * delta_h, j * delta_h) - (matrix[i - 1][j] + matrix[i][j - 1] + matrix[i + 1][j] + matrix[i][j + 1]);
			index++;
		}
	}

	// Show matrix Boundary
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			outfile1 << setw(10) << matrix[i][j];
		}
		outfile1 << endl;
	}

	// Show matrix F
	for (int i = 0; i < sizeF; i++) {
		outfile2 << setw(10) << matrixF[i] << endl;
	}

	outfile1.close();
	outfile2.close();

	return (matrixF);
}