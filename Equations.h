#ifndef EQUATION_H
#define EQUATION_H

#include<iostream>

using namespace std;

double** equation(double **A, double *y, int size) {
	ofstream outfile ("Equations.dat");

	double** matrix = new double*[size];
        for (int i = 0; i < size; i++)
                matrix[i] = new double[size + 1];

    for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size + 1; j++) {
    		if (j < size)
    			matrix[i][j] = A[i][j];
    		else
    			matrix[i][j] = y[i];
    	}
    }

    for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			outfile << setw(15) << matrix[i][j];
		}
		outfile << endl;
	}

	outfile.close();

	return matrix;
}

#endif