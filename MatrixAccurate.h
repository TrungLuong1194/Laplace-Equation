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
	for (int j = 1; j < size - 1; j++) {
		for (int i = size - 2; i >= 1; i--) {
			matrix[index] = funtionU4(j * delta_h, (size - 1 - i) * delta_h);
			index++;
		}
	}

	// Show matrix accurate
	for (int i = 0; i < sizeF; i++) {
		outfile << "u[" << i << "]="  << matrix[i] << endl;
	}

	outfile.close();

	return matrix;
}