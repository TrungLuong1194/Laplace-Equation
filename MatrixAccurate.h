#include<iostream>
#include<fstream>
#include<iomanip>

#include "Function.h"

using namespace std;

// Return matrix F
double* matrixAccurate(int sizeMatrix, double topBoundary, double rightBoundary) {
	ofstream outfile ("matrixAccurate.dat");

	int size = sizeMatrix + 2;

	double delta_h = topBoundary / (size - 1);

	int sizeF = sizeMatrix * sizeMatrix;
	double* matrix = new double[sizeF];
	int index = 0;

	// create matrix accurate
	for (int i = 1; i < size - 1; i++) {
		for (int j = 1; j < size - 1; j++) {
			matrix[index] = funtionExsol(i * delta_h, j * delta_h);
			index++;
		}
	}

	// Show matrix accurate
	for (int i = 0; i < sizeF; i++) {
		outfile << setw(3) << matrix[i] << endl;
	}

	outfile.close();

	return matrix;
}