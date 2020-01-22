#include<iostream>
#include<fstream>
#include<iomanip>

#include "MatrixA.h"
#include "Function.h"
#include "MatrixF.h"

using namespace std;

// Return matrix U
double** matrixSb(int sizeMatrix, double topBoundary, double rightBoundary) {

	ofstream outfile ("matrixSb.dat");

	int size = sizeMatrix * sizeMatrix;

	double delta_h = topBoundary / (sizeMatrix + 1);

	int** matrix = new int*[sizeMatrix];
        for (int i = 0; i < sizeMatrix; i++)
            matrix[i] = new int[sizeMatrix];

    double* matrixIndex = new double[size];

	// double x0 = (sizeMatrix / 2) * delta_h;
    int x0 = sizeMatrix / 2;

	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int count = 0;

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            matrix[i][j] = count;
            count++;
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i > x0) {
                n1++;
                matrixIndex[n1 - 1] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i < x0) {
                n2++;
                matrixIndex[n1 + n2 - 1] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i == x0) {
                n3++;
                matrixIndex[n1 + n2 + n3 - 1] = matrix[i][j];
            }
        }
    }

	// Return matrix A
	double** matrix_A= new double*[size];
        for (int i = 0; i < size; i++)
                matrix_A[i] = new double[size];

    matrix_A = matrixA(sizeMatrix);

    // Create matrix A11
    double** matrixA11= new double*[n1];
        for (int i = 0; i < n1; i++)
                matrixA11[i] = new double[n1];

    int inew, jnew;

    for (int i = 0; i < n1; i++) {
    	for (int j = 0; j < n1; j++) {
            inew = matrixIndex[i];
            jnew = matrixIndex[j];

    		matrixA11[i][j] = matrix_A[inew][jnew];
    	}
    }

    // Create matrix A13
    double** matrixA13= new double*[n1];
        for (int i = 0; i < n1; i++)
                matrixA13[i] = new double[n3];

    for (int i = 0; i < n1; i++) {
    	for (int j = 0; j < n3; j++) {
            inew = matrixIndex[i];
    		jnew = matrixIndex[n1 + n2 + j];

    		matrixA13[i][j] = matrix_A[inew][jnew];
    	}
    }

    // Create matrix A22
    double** matrixA22= new double*[n2];
        for (int i = 0; i < n2; i++)
                matrixA22[i] = new double[n2];

    for (int i = 0; i < n2; i++) {
    	for (int j = 0; j < n2; j++) {
            inew = matrixIndex[n1 + i];
            jnew = matrixIndex[n1 + j];

    		matrixA22[i][j] = matrix_A[inew][jnew];
    	}
    }

    // Create matrix A23
    double** matrixA23= new double*[n2];
        for (int i = 0; i < n2; i++)
                matrixA23[i] = new double[n3];

    for (int i = 0; i < n2; i++) {
    	for (int j = 0; j < n3; j++) {
            inew = matrixIndex[n1 + i];
            jnew = matrixIndex[n1 + n2 + j];

    		matrixA23[i][j] = matrix_A[inew][jnew];
    	}
    }

    // Create matrix A33
    double** matrixA33= new double*[n3];
        for (int i = 0; i < n3; i++)
                matrixA33[i] = new double[n3];

    for (int i = 0; i < n3; i++) {
    	for (int j = 0; j < n3; j++) {
            inew = matrixIndex[n1 + n2 + i];
            jnew = matrixIndex[n1 + n2 + j];

    		matrixA33[i][j] = matrix_A[inew][jnew];
    	}
    }

    // Show n1, n2, n3
    outfile << "n1 = " << n1;
    outfile << endl;
    outfile << "n2 = " << n2;
    outfile << endl;
    outfile << "n3 = " << n3;
    outfile << endl;
    outfile << endl;
    
    // Create matrix A13^T
    double** matrixA13T= new double*[n3];
        for (int i = 0; i < n3; i++)
                matrixA13T[i] = new double[n1];

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n1; j++) {

            matrixA13T[i][j] = matrixA13[j][i];
        }
    }

    // Output matrix A13^T
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "A13^T = " << endl;

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n1; j++) {

            outfile << setw(10) << matrixA13T[i][j];
        }
        outfile << endl;
    }
    outfile << endl;


    // Create matrix A23^T
    double** matrixA23T= new double*[n3];
        for (int i = 0; i < n3; i++)
                matrixA23T[i] = new double[n2];

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n2; j++) {

            matrixA23T[i][j] = matrixA23[j][i];
        }
    }

    // Output matrix A23^T
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "A23^T = " << endl;

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n2; j++) {

            outfile << setw(10) << matrixA23T[i][j];
        }
        outfile << endl;
    }
    outfile << endl;

    // Create matrix A11^-1
    double** matrixA11I= new double*[n1];
        for (int i = 0; i < n1; i++)
                matrixA11I[i] = new double[n1];

    matrixA11I = matrixInverse(matrixA11, n1);

    // Output matrix A11^-1
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "A11^-1 = " << endl;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {

            outfile << setw(13) << matrixA11I[i][j];
        }
        outfile << endl;
    }
    outfile << endl;

    // Create matrix A22^-1
    double** matrixA22I= new double*[n2];
        for (int i = 0; i < n2; i++)
                matrixA22I[i] = new double[n2];

    matrixA22I = matrixInverse(matrixA22, n2);

    // Output matrix A22^-1
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "A22^-1 = " << endl;

    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {

            outfile << setw(13) << matrixA22I[i][j];
        }
        outfile << endl;
    }
    outfile << endl;

    // Create matrix S
    double** matrixS= new double*[n3];
        for (int i = 0; i < n3; i++)
                matrixS[i] = new double[n3];

    double** matrixTmp1,** matrixTmp2,** matrixTmp3,** matrixTmp4;

    matrixTmp1 = multiplyMatrix3(matrixA13T, matrixA11I, n3, n1, n1);
    matrixTmp2 = multiplyMatrix3(matrixTmp1, matrixA13, n3, n1, n3);

    matrixTmp3 = multiplyMatrix3(matrixA23T, matrixA22I, n3, n2, n2);
    matrixTmp4 = multiplyMatrix3(matrixTmp3, matrixA23, n3, n2, n3);

    matrixS = subtractMatrix(matrixA33, matrixTmp2, matrixTmp4, n3);

    // Output matrix S
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "S = " << endl;

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n3; j++) {

            outfile << setw(13) << matrixS[i][j];
        }
        outfile << endl;
    }
    outfile << endl;

    //---------------------------------------------------------------------------------------------------
    // Return matrix b3~
    double* matrix_F = matrixF(sizeMatrix, topBoundary, rightBoundary);

    double* matrixB = new double[size];

    n1 = 0;
    n2 = 0;
    n3 = 0;

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i > x0) {
                n1++;
                matrixB[n1 - 1] = matrix_F[matrix[i][j]];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i < x0) {
                n2++;
                matrixB[n1 + n2 - 1] = matrix_F[matrix[i][j]];
            }
        }
    }

    for (int j = 0; j < sizeMatrix; j++) {
        for (int i = sizeMatrix - 1; i >= 0; i--) {
            if (i == x0) {
                n3++;
                matrixB[n1 + n2 + n3 - 1] = matrix_F[matrix[i][j]];
            }
        }
    }

    // create vector b1
    double* matrixB1 = new double[n1];

    for (int i = 0; i < n1; i++) {
        matrixB1[i] = matrixB[i];
    }

    // Output vector b1
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "b1 = " << endl;
    for (int i = 0; i < n1; i++) {
        outfile << matrixB1[i] << endl;
    }
    outfile << endl;

    // create vector b2
    double* matrixB2 = new double[n2];

    for (int i = 0; i < n2; i++) {
        matrixB2[i] = matrixB[i + n1];
    }

    // Output vector b2
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "b2 = " << endl;
    for (int i = 0; i < n2; i++) {
        outfile << matrixB2[i] << endl;
    }
    outfile << endl;

    // create vector b3
    double* matrixB3 = new double[n3];

    for (int i = 0; i < n3; i++) {
        matrixB3[i] = matrixB[i + n1 + n2];
    }

    // Output vector b3
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "b3 = " << endl;
    for (int i = 0; i < n3; i++) {
        outfile << matrixB3[i] << endl;
    }
    outfile << endl;

    // Create matrix B3 New
    double* matrixB3New = new double[n3];
    double* matrixTmp5, * matrixTmp6;

    matrixTmp5 = multiplyMatrix4(matrixTmp1, matrixB1, n3, n1);

    matrixTmp6 = multiplyMatrix4(matrixTmp3, matrixB2, n3, n2);

    matrixB3New = subtractVector(matrixB3, matrixTmp5, matrixTmp6, n3);

    // Output vector b3~
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "b3~ = " << endl;
    for (int i = 0; i < n3; i++) {
        outfile << matrixB3New[i] << endl;
    }
    outfile << endl;

    //--------------------------------------------------------------------------------------
    // Calculate U3
    double* matrixU3 = new double[n3];
    matrixU3 = luWithPivot(matrixS, matrixB3New, n3);

    // Output vector U3
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "U3 = " << endl;
    for (int i = 0; i < n3; i++) {
        outfile << matrixU3[i] << endl;
    }
    outfile << endl;

    double* matrixU1 = new double[n1];
    double* matrixTmp7, * matrixTmp8;

    matrixTmp7 = multiplyMatrix4(matrixA13, matrixU3, n1, n3);
    matrixTmp8 = subtractVector2(matrixB1, matrixTmp7, n1);
    matrixU1 = multiplyMatrix4(matrixA11I, matrixTmp8, n1, n1);

    // Output vector U1
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "U1 = " << endl;
    for (int i = 0; i < n1; i++) {
        outfile << matrixU1[i] << endl;
    }
    outfile << endl;

    double* matrixU2 = new double[n2];
    double* matrixTmp9, * matrixTmp10;

    matrixTmp9 = multiplyMatrix4(matrixA23, matrixU3, n2, n3);
    matrixTmp10 = subtractVector2(matrixB2, matrixTmp9, n2);
    matrixU2 = multiplyMatrix4(matrixA22I, matrixTmp10, n2, n2);

    // Output vector U2
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "U2 = " << endl;
    for (int i = 0; i < n2; i++) {
        outfile << matrixU2[i] << endl;
    }
    outfile << endl;

    double* matrixU = new double[size];

    for (int i = 0; i < n1; i++) {
        matrixU[i] = matrixU1[i];
    }

    for (int i = 0; i < n2; i++) {
        matrixU[i + n1] = matrixU2[i];
    }

     for (int i = 0; i < n3; i++) {
        matrixU[i + n1 + n2] = matrixU3[i];
    }

    // Output vector U
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "U = " << endl;
    for (int i = 0; i < size; i++) {
        outfile << matrixU[i] << endl;
    }
    outfile << endl;

    // Matrix Original
    double* matrixU_Ori = new double[size];
    int index;

    for (int i = 0; i < size; i++) {
        index = matrixIndex[i];
        matrixU_Ori[index] = matrixU[i];
    }

    // Show matrix U original
    outfile << "-------------------------------------------------------------" << endl;
    outfile << "U original = " << endl;
    for (int i = 0; i < size; i++) {
        outfile << matrixU_Ori[i] << endl;
    }

	outfile.close();

	return (matrixS);
}