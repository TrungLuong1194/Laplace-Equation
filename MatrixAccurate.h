#include<iostream>
#include<fstream>
#include<iomanip>

#include "Function.h"

using namespace std;

// Return matrix F
double* matrixAccurate(int sizeMatrix, double delta_h) {
	ofstream outfile ("matrixAccurate.dat");

	int size = sizeMatrix * sizeMatrix;
	double* matrix = new double[size];
	int index = 0;

	// create matrix accurate
	for (int i = 1; i <= sizeMatrix; i++) {
		for (int j = 1; j <= sizeMatrix; j++) {
			matrix[index] = funtionExsol(i * delta_h, j * delta_h);
			index++;
		}
	}

	// Show matrix accurate
	for (int i = 0; i < size; i++) {
		outfile << setw(3) << matrix[i] << endl;
	}

	outfile.close();

	return matrix;
}