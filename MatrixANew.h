#include<iostream>
#include<fstream>
#include<iomanip>

#include "MatrixA.h"

using namespace std;

// Return matrix A New
double** matrixANew(int sizeMatrix, double topBoundary, double rightBoundary) {

	ofstream outfile ("matrixANew.dat");
    ofstream outfile1 ("matrixIndex.dat");

	int size = sizeMatrix * sizeMatrix;

	double delta_h = topBoundary / (sizeMatrix + 1);

	double** matrix = new double*[sizeMatrix];
        for (int i = 0; i < sizeMatrix; i++)
                matrix[i] = new double[sizeMatrix];

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

    for (int i = 0; i < size; i++) {
        outfile1 << setw(10) << matrixIndex[i] << endl;
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

    // Create matrix A new
    double** matrixNew= new double*[size];
        for (int i = 0; i < size; i++)
                matrixNew[i] = new double[size];

    for (int i = 0; i < n1; i++) {
    	for (int j = 0; j < n1; j++) {
    		matrixNew[i][j] = matrixA11[i][j];
    	}
    }

    for (int i = 0; i < n1; i++) {
    	for (int j = 0; j < n2; j++) {
    		int jnew = n1 + j;

    		matrixNew[i][jnew] = 0;
    	}
    }

    for (int i = 0; i < n1; i++) {
    	for (int j = 0; j < n3; j++) {
    		int jnew = n1 + n2 + j;

    		matrixNew[i][jnew] = matrixA13[i][j];
    	}
    }

    for (int i = 0; i < n2; i++) {
    	for (int j = 0; j < n1; j++) {
    		int inew = n1 + i;

    		matrixNew[inew][j] = 0;
    	}
    }

    for (int i = 0; i < n2; i++) {
    	for (int j = 0; j < n2; j++) {
    		int inew = n1 + i;
    		int jnew = n1 + j;

    		matrixNew[inew][jnew] = matrixA22[i][j];
    	}
    }

    for (int i = 0; i < n2; i++) {
    	for (int j = 0; j < n3; j++) {
    		int inew = n1 + i;
    		int jnew = n1 + n2 + j;

    		matrixNew[inew][jnew] = matrixA23[i][j];
    	}
    }

    for (int i = 0; i < n3; i++) {
    	for (int j = 0; j < n1; j++) {
    		int inew = n1 + n2 + i;

    		matrixNew[inew][j] = matrixA13[j][i];
    	}
    }

    for (int i = 0; i < n3; i++) {
    	for (int j = 0; j < n2; j++) {
    		int inew = n1 + n2 + i;
    		int jnew = n1 + j;

    		matrixNew[inew][jnew] = matrixA23[j][i];
    	}
    }

    for (int i = 0; i < n3; i++) {
    	for (int j = 0; j < n3; j++) {
    		int inew = n1 + n2 + i;
    		int jnew = n1 + n2 + j;

    		matrixNew[inew][jnew] = matrixA33[i][j];
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

    // Print matrix A new
    for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			outfile << setw(3) << matrixNew[i][j];
		}
		outfile << endl;
	}

	outfile.close();
    outfile1.close();

	return (matrixNew);
}