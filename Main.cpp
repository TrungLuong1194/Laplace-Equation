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
#include "Jacobi.h"
#include "LU.h"
#include "MatrixSb.h"
#include "LU_transform.h"

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
	double *matrix_U_Gauss;

	ofstream outfile ("result.dat");

	outfile << "Size Matrix: " << sizeMatrix << endl;

	cout << "--------------------------------Result Gauss-----------------------------------" << endl;
	outfile << "--------------------------------Result Gauss-----------------------------------" << endl;

	matrix_U_Gauss = gauss(matrix_A, matrix_F, size);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U_Gauss[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile << "u[" << i << "]=" << matrix_U_Gauss[i] << endl;

   	cout << "--------------------------------Sai so Gauss---------------------------------------" << endl;
   	outfile << "--------------------------------Sai so Gauss---------------------------------------" << endl;

   	double* matrix_Accurate = matrixAccurate(sizeMatrix, topBoundary, rightBoundary);

   	double sum = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum += pow(((matrix_U_Gauss[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum) << endl;
    outfile << sqrt(sum) << endl;

    cout << "--------------------------------Result Jacobi-----------------------------------" << endl;
    outfile << "--------------------------------Result Jacobi-----------------------------------" << endl;

    double *matrix_U_Jacobi;
	matrix_U_Jacobi = solve_jacobi_sequential(matrix_A, size, matrix_F);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U_Jacobi[i] << endl;

    for (int i = 0; i < size; i++) 
    	outfile << "u[" << i << "]=" << matrix_U_Jacobi[i] << endl;

   	cout << "--------------------------------Sai so Jacobi---------------------------------------" << endl;
   	outfile << "--------------------------------Sai so Jacobi---------------------------------------" << endl;

   	double sum1 = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum1 += pow(((matrix_U_Jacobi[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum1) << endl;
    outfile << sqrt(sum1) << endl;

    // ------------------------------Matrix A New-------------------------------
	// double** matrix_ANew = matrixANew(sizeMatrix, topBoundary, rightBoundary);

	// double* matrix_FNew = matrixFNew(sizeMatrix, topBoundary, rightBoundary);

	double *matrix_U_LU;

	cout << "--------------------------------Result LU Method-----------------------------------" << endl;
	outfile << "--------------------------------Result LU Method-----------------------------------" << endl;

	// matrix_U_LU = luWithPivot(matrix_ANew, matrix_FNew, size);

	matrix_U_LU = lu_transform(sizeMatrix, topBoundary, rightBoundary);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U_LU[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile << "u[" << i << "]=" << matrix_U_LU[i] << endl;

    cout << "--------------------------------Sai so LU---------------------------------------" << endl;
    outfile << "--------------------------------Sai so LU---------------------------------------" << endl;

   	double sum2 = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum2 += pow(((matrix_U_LU[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum2) << endl;
    outfile << sqrt(sum2) << endl;

   	 // ------------------------------Matrix S-------------------------------
	double* matrix_U_LastMethod;

	cout << "--------------------------------Result Last Method-----------------------------------" << endl;
	outfile << "--------------------------------Result Last Method-----------------------------------" << endl;

	matrix_U_LastMethod = matrixSb(sizeMatrix, topBoundary, rightBoundary);

	for (int i = 0; i < size; i++) 
    	cout << "u[" << i << "]=" << matrix_U_LastMethod[i] << endl;

	for (int i = 0; i < size; i++) 
    	outfile << "u[" << i << "]=" << matrix_U_LastMethod[i] << endl;

    cout << "--------------------------------Sai so Last Method---------------------------------------" << endl;
    outfile << "--------------------------------Sai so Last Method---------------------------------------" << endl;

   	double sum3 = 0.0;

   	for (int i = 0; i < size; i++) 
    	sum3 += pow(((matrix_U_LastMethod[i] - matrix_Accurate[i]) / matrix_Accurate[i]), 2);

    cout << sqrt(sum3) << endl;
    outfile << sqrt(sum3) << endl;

    outfile.close();

	return 0;
}