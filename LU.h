#include<iostream>

#include "Function.h"

using namespace std;

double* luWithPivot(double** a, double* b, int n) {
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

    double maxColumn;
    int indexRow;
    int index;

    for (int j = 0; j < n; j++) {
    	index = 0;

    	while(true) {
    		if (matrixIndex[index] != 1) {
    			maxColumn = a[index][j];
    			break;
    		} else	{
    			index++;
    		}
    	}

    	indexRow = index;

    	for (int i = index + 1; i < n; i++) {
    		if ((a[i][j] > maxColumn) && (matrixIndex[i] != 1)) {
    			maxColumn = a[i][j];
    			indexRow = i;
    		}
    	}

    	matrixP[indexRow][j] = 1;
    	matrixIndex[indexRow] = 1;
    }



    // Print matrix P
    outfile << "Matrix P" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(3) << matrixP[i][j];
		}
		outfile << endl;
	}

	// return matrix transposition P
	double** matrixPT = new double*[n];
        for (int i = 0; i < n; i++)
                matrixPT[i] = new double[n];

    matrixPT = matrixTransposition(matrixP, n);

    // Print matrix P^T
    outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix P^T" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(3) << matrixPT[i][j];
		}
		outfile << endl;
	}

	// return P^T * a
	double** matrix = new double*[n];
        for (int i = 0; i < n; i++)
                matrix[i] = new double[n];

    matrix = multiplyMatrix(matrixPT, a, n);

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
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix L" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrixL[i][j];
		}
		outfile << endl;
	}

	// Print matrix U
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix U" << endl;
    outfile << endl;

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
   	outfile << "--------------------------------------------------------------" << endl;
   	outfile << "Check result" << endl;
   	outfile << endl;
    outfile << "Matrix M = L * U" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrixM[i][j];
		}
		outfile << endl;
	}

	// Print matrix P^T * A
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix P^T * A" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			outfile << setw(10) << matrix[i][j];
		}
		outfile << endl;
	}

	// return bNew = P^T * b
	double* bNew = new double[n];

    bNew = multiplyMatrix2(matrixPT, b, n);

    // Print matrix bNew
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix bNew = P^T * b" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++) {
		outfile << setw(10) << bNew[i] << endl;
	}

    // return z (L * z = bNew)
    double* z = new double[n];
    double tmp;

    z[0] = bNew[0] / matrixL[0][0];

    for (int i = 1; i < n; i++) {
    	tmp = 0.0;
    	for (int j = 0; j < i; j++) {
    		tmp += z[j] * matrixL[i][j];
    	}

    	z[i] = (bNew[i] - tmp) / matrixL[i][i];
    }

    // Print matrix z
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix z (L * z = bNew)" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++) {
		outfile << setw(10) << z[i] << endl;
	}

	// return x (U * x = z)
    double* x = new double[n];

    x[n - 1] = z[n - 1] / matrixU[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--) {
    	tmp = 0.0;
    	for (int j = n - 1; j > i; j--) {
    		tmp += x[j] * matrixU[i][j];
    	}

    	x[i] = (z[i] - tmp) / matrixU[i][i];
    }

    // Print matrix x
   	outfile << "--------------------------------------------------------------" << endl;
    outfile << "Matrix x (U * x = z)" << endl;
    outfile << endl;

    for (int i = 0; i < n; i++) {
		outfile << setw(10) << x[i] << endl;
	}

   	outfile.close();

   	return x;
}