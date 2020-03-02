#include<iostream>
#include<fstream>
#include<iomanip>

#ifndef MATRIXA_H
#define MATRIXA_H

using namespace std;

//Rturn matrix A
double** matrixA(int sizeMatrix) {
	ofstream outfile ("matrixA.dat");

	int size = sizeMatrix * sizeMatrix;

	double** matrix = new double*[size];
        for (int i = 0; i < size; i++)
                matrix[i] = new double[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
		
			matrix[i][j] = 0;
		}
	}

	// Create matrix A
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				matrix[i][j] = -4;
				if ((i < size-1) && (i % sizeMatrix != (sizeMatrix-1))) {
					matrix[i][j+1] = 1;
					matrix[i+1][j] = 1;
				}
				if (i < size-sizeMatrix) {
				matrix[i][j+sizeMatrix] = 1;
				matrix[i+sizeMatrix][j] = 1;
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			outfile << setw(3) << matrix[i][j];
		}
		outfile << endl;
	}

	outfile.close();

	return (matrix);
}

#endif