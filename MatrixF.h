#include<iostream>
#include<fstream>
#include<iomanip>

#include "Function.h"

using namespace std;

// Return matrix F
double* matrixF(int sizeMatrix, double topBoundary, double rightBoundary, double delta_h, double F) {
	ofstream outfile1 ("matrixBoundary.dat");
	ofstream outfile2 ("matrixF.dat");

	int size = sizeMatrix + 2;

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
			if (j == 0) 
				matrix[i][j] = topBoundary;
			if (i == size - 1)
				matrix[i][j] = rightBoundary;
		}
	}

	int sizeF = sizeMatrix * sizeMatrix;
	double* matrixF = new double[sizeF];
	int index = 0;

	// create matrix F
	for (int i = 1; i < size - 1; i++) {
		for (int j = 1; j < size - 1; j++) {
			matrixF[index] = (delta_h * delta_h * F) - funtionF((i - 1) * delta_h, j * delta_h) - funtionF(i* delta_h, (j + 1) * delta_h) 
			- (matrix[i - 1][j] + matrix[i][j - 1] + matrix[i + 1][j] + matrix[i][j + 1]);
			index++;
		}
	}

	// Show matrix Boundary
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			outfile1 << setw(3) << matrix[i][j];
		}
		outfile1 << endl;
	}

	// Show matrix F
	for (int i = 0; i < sizeF; i++) {
		outfile2 << setw(3) << matrixF[i] << endl;
	}

	outfile1.close();
	outfile2.close();

	return (matrixF);
}