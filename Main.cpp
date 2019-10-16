#include<iostream>
#include<fstream>
#include<iomanip>

#include "MatrixA.h"
#include "MatrixF.h"
#include "Gauss.h"

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

	cout <<"Input deta h: ";
	cin >> delta_h;

	double F;

	cout <<"Input function F: ";
	cin >> F;

	double* matrix_F = matrixF(sizeMatrix, topBoundary, rightBoundary, delta_h, F);

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

	return 0;
}