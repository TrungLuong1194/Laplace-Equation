#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>

#include "MatrixA.h"
#include "MatrixF.h"
#include "Gauss.h"
#include "MatrixAccurate.h"

using namespace std;

int main() {
	int sizeMatrix;

	cout << "Input size of matrix: ";
	cin >> sizeMatrix;

	int size = sizeMatrix * sizeMatrix;

	// ------------------------------Matrix A-------------------------------
	double** matrix_A = matrixA(sizeMatrix);

	cout << "------------------------------Matrix A-------------------------------------" << endl;

	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			cout << setw(3) << matrix_A[i][j];
		}
		cout << endl;
	}

	cout << "---------------------------------------------------------------------------" << endl;

	// ----------------------------- Matrix F ---------------------------
	int topBoundary;                    // Bien tren
	int rightBoundary;					// Bien phai

	cout << "Input top boundary: ";
	cin >> topBoundary;
	cout << "Input right boundary: ";
	cin >> rightBoundary;

	double delta_h;

	cout <<"Input delta h: ";
	cin >> delta_h;

	double* matrix_F = matrixF(sizeMatrix, topBoundary, rightBoundary, delta_h);

	cout << "------------------------------Matrix F-------------------------------------" << endl;

	for (int i = 0; i < size; i++) {
		cout << setw(3) << matrix_F[i] << endl;
	}

	// -------------------------------Gauss-Jordan---------------------------
	double *matrix_U;

	ofstream outfile ("result_U.dat");

	cout << "--------------------------------Result---------------------------------------" << endl;

	matrix_U = gauss(matrix_A, matrix_F, size);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile << matrix_U[i] << endl;

   	outfile.close();

   	cout << "--------------------------------Sai so---------------------------------------" << endl;

   	double* matrix_Accurate = matrixAccurate(sizeMatrix, delta_h);

   	double sum = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum += pow(((matrix_U[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum);

	return 0;
}