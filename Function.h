#ifndef FUNCTION_H
#define FUNCTION_H

double funtionF(double x, double y) {
	// return 2 * x * (x - 1) + 2 * y * (y - 1);
	return 4.0;
}

double funtionU1(double x, double y) {
	return x * (x - 1) * y * (y - 1);
}

double funtionU2(double x, double y) {
	return (x - 1) * (x - 1) + (y - 1) * (y - 1);
}

double** multiplyMatrix(double** a, double** b, int n) {
	double** matrix = new double*[n];
        for (int i = 0; i < n; i++)
                matrix[i] = new double[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
			
			for (int k = 0; k < n; k++) {
				matrix[i][j] += a[i][k] * b[k][j];
			}

		}
	}

	return matrix;
}

#endif