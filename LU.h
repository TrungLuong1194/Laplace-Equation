#include<iostream>

#include "Function.h"

using namespace std;

void luWithPivot(double **a, int n) {
	ofstream outfile ("matrixPLU.dat");

	// matrix L
	double** matrixL = new double*[n];
        for (int i = 0; i < n; i++)
                matrixL[i] = new double[n];

    // matrix U
	double** matrixU = new double*[n];
        for (int i = 0; i < n; i++)
                matrixU[i] = new double[n];

    // matrix P
	double** matrixP = new double*[n];
        for (int i = 0; i < n; i++)
                matrixP[i] = new double[n];

    // matrix index
    double* matrixIndex = new double[n];

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		matrixP[i][j] = 0;
    	}
    }

    // create matrix P
    double maxRow;
    int indexColumn;
    int index;

    for (int i = 0; i < n; i++) {
    	index = 0;

    	while(true) {
    		if (matrixIndex[index] != 1) {
    			maxRow = a[i][index];
    			break;
    		} else	{
    			index++;
    		}
    	}

    	indexColumn = index;

    	for (int j = index + 1; j < n; j++) {
    		if ((a[i][j] > maxRow) && (matrixIndex[j] != 1)) {
    			maxRow = a[i][j];
    			indexColumn = j;
    		}
    	}

    	matrixP[i][indexColumn] = 1;
    	matrixIndex[indexColumn] = 1;
    }

    // Print matrix P
    outfile << "Matrix P" << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(3) << matrixP[i][j];
		}
		outfile << endl;
	}

	// return P * a
	double** matrix = new double*[n];
        for (int i = 0; i < n; i++)
                matrix[i] = new double[n];

    matrix = multiplyMatrix(matrixP, a, n);

	// create matrix L vs U
	for (int i = 0; i < n; i++) {
      	for (int j = 0; j < n; j++) {
	        if (j < i)
	        	matrixL[j][i] = 0;
	        else {
	            matrixL[j][i] = matrix[j][i];

	            for (int k = 0; k < i; k++) {
	               	matrixL[j][i] = matrixL[j][i] - matrixL[j][k] * matrixU[k][i];
	            }
	        }
      	}

	    for (int j = 0; j < n; j++) {
	        if (j < i)
	            matrixU[i][j] = 0;
	        else if (j == i)
	            matrixU[i][j] = 1;
	        else {
	            matrixU[i][j] = matrix[i][j] / matrixL[i][i];

	            for (int k = 0; k < i; k++) {
	                matrixU[i][j] = matrixU[i][j] - ((matrixL[i][k] * matrixU[k][j]) / matrixL[i][i]);
	            }
	        }
	    }
   	}

   	// Print matrix L
   	outfile << endl;
    outfile << "Matrix L" << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrixL[i][j];
		}
		outfile << endl;
	}

	// Print matrix U
   	outfile << endl;
    outfile << "Matrix U" << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrixU[i][j];
		}
		outfile << endl;
	}

	// Check result
	double** matrixM = new double*[n];
        for (int i = 0; i < n; i++)
                matrixM[i] = new double[n];

    matrixM = multiplyMatrix(matrixL, matrixU, n);

    // Print matrix M = L * U
   	outfile << endl;
   	outfile << "Check result" << endl;
    outfile << "Matrix M = L * U" << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrixM[i][j];
		}
		outfile << endl;
	}

	// Print matrix P * A
   	outfile << endl;
    outfile << "Matrix P * A" << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrix[i][j];
		}
		outfile << endl;
	}

   	outfile.close();
}