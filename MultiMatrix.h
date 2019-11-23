double* multiMatrix(double** A, double* B, int n) {
	double* C = new double[n];

	for (int i = 0; i < n; i++) {
		C[i] = 0;
		for (int j = 0; j < n; j++) {
			C[i] += A[i][j] * B[j];
		}
	}

	return C;
}