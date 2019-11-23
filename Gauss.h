#include<iostream>
#include "Equations.h"

using namespace std;

double* gauss(double **a, double* y, int n) {
    double app,sum,mult;
    int i,j,k,p;

    double** A;
    double* temp = new double[n];

    A = equation(a, y, n);

       for(i=0;i<(n);i++){
            app = A[i][i];
//initialization of p
            p = i;
//find largest no of the columns and row no. of largest no.
            for(k = i+1; k < n; k++)
            if(fabs(app) < fabs(A[k][i])){
               app = A[k][i] ;
               p = k;
            }
//swaping the elements of diagonal row and row containing largest no
            for(j = 0; j <= n; j++)
            {
                temp[j] = A[p][j];
                A[p][j] = A[i][j];
                A[i][j] = temp[j];
            }
//calculating triangular matrix
            for(j=i+1;j<n;j++){
                mult = A[j][i]/A[i][i];
                for(k=0;k<=n;k++)
                    A[j][k] -= mult*A[i][k];
            }
       }
//for calculating value of z,y,x via backward substitution method
        for(i=n-1;i>=0;i--)
        {
            sum = 0;
            for(j=i+1;j<n;j++)
                sum += A[i][j]*temp[j];
            temp[i] = (A[i][n]-sum)/A[i][i];
        }

    return temp;

}