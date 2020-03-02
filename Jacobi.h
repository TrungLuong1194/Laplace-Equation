#include<iostream>
#include "Equations.h"

#define ITERATION_LIMIT 333
#define EPSILON 0.0000001

void init_array_sequential(double* array, int array_size){
    for (int i = 0; i < array_size; i++) {
        array[i] = 0;
    }
}

double* clone_array_sequential(double* array, int array_length){
    double* output = new double[array_length];
    for (int i = 0; i < array_length; i++) {
        output[i] = array[i];
    }
    return output;
}

double* solve_jacobi_sequential(double** matrix, int matrix_size, double* right_hand_side) {
    double* solution = new double[matrix_size];
    double* last_iteration = new double[matrix_size];
    
    // Just for initialization ..
    init_array_sequential(solution, matrix_size);
    
    for (int i = 0; i < ITERATION_LIMIT; i++){
        last_iteration = clone_array_sequential(solution, matrix_size);
        for (int j = 0; j < matrix_size; j++) {
            double sigma_value = 0;
            for (int k = 0; k < matrix_size; k++) {
                if (j != k) {
                    sigma_value += matrix[j][k] * solution[k];
                }
            }
            solution[j] = (right_hand_side[j] - sigma_value) / matrix[j][j];
        }

        // Checking for the stopping condition ...
        int stopping_count = 0;
        for (int s = 0; s < matrix_size; s++) {
            if (abs(last_iteration[s] - solution[s]) <= EPSILON) {
                stopping_count++;
            }
        }

        if (stopping_count == matrix_size) break;
    }

    return solution;
}