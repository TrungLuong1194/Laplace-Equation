#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>

#include "MatrixA.h"
#include "MatrixANew.h"
#include "MatrixF.h"
#include "MatrixFNew.h"
#include "Gauss.h"
#include "MatrixAccurate.h"
#include "jacobi.h"
#include "LU.h"

using namespace std;

int main() {
	int sizeMatrix;

	cout << "Input size of matrix: ";
	cin >> sizeMatrix;

	int size = sizeMatrix * sizeMatrix;

	// ------------------------------Matrix A-------------------------------
	double** matrix_A = matrixA(sizeMatrix);

	// cout << "------------------------------Matrix A-------------------------------------" << endl;

	// for (int j = 0; j < size; j++)
	// {
	// 	for (int i = 0; i < size; i++)
	// 	{
	// 		cout << setw(3) << matrix_A[i][j];
	// 	}
	// 	cout << endl;
	// }

	cout << "---------------------------------------------------------------------------" << endl;

	// ----------------------------- Matrix F ---------------------------
	double topBoundary;                    // Bien tren
	double rightBoundary;					// Bien phai

	cout << "Input top boundary: ";
	cin >> topBoundary;
	cout << "Input right boundary: ";
	cin >> rightBoundary;

	double* matrix_F = matrixF(sizeMatrix, topBoundary, rightBoundary);

	// cout << "------------------------------Matrix F-------------------------------------" << endl;

	// for (int i = 0; i < size; i++) {
	// 	cout << setw(3) << matrix_F[i] << endl;
	// }

	// -------------------------------Gauss-Jordan---------------------------
	double *matrix_U;

	ofstream outfile ("result_U.dat");

	cout << "--------------------------------Result Gauss-----------------------------------" << endl;

	matrix_U = gauss(matrix_A, matrix_F, size);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile << matrix_U[i] << endl;

   	outfile.close();

   	cout << "--------------------------------Sai so Gauss---------------------------------------" << endl;

   	double* matrix_Accurate = matrixAccurate(sizeMatrix, topBoundary, rightBoundary);

   	double sum = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum += pow(((matrix_U[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum) << endl;

    // double epx = abs(matrix_U[0] - matrix_Accurate[0]);
    // double tmp = 0.0;

    // for (int i = 1; i < size; i++) {
    // 	tmp = abs(matrix_U[i] - matrix_Accurate[i]);
    // 	if (tmp > epx)
    // 		epx = tmp;
    // }

    // cout << epx << endl;



    cout << "--------------------------------Result Jacobi-----------------------------------" << endl;
    double *matrix_J;
	matrix_J = solve_jacobi_sequential(matrix_A, size, matrix_F);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_J[i] << endl;

   	cout << "--------------------------------Sai so Jacobi---------------------------------------" << endl;

   	double sum1 = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum1 += pow(((matrix_J[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum1) << endl;





    // ------------------------------Matrix A New-------------------------------
	double** matrix_ANew = matrixANew(sizeMatrix, topBoundary, rightBoundary);

	double* matrix_FNew = matrixFNew(sizeMatrix, topBoundary, rightBoundary);

	double *matrix_UNew;

	ofstream outfile1 ("result_UNew.dat");

	cout << "--------------------------------Result Gauss New-----------------------------------" << endl;

	matrix_UNew = gauss(matrix_ANew, matrix_FNew, size);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_UNew[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile1 << matrix_UNew[i] << endl;

   	outfile1.close();

   	cout << "--------------------------------Result LU Method-----------------------------------" << endl;
   	luWithPivot(matrix_ANew, size);









	return 0;
}