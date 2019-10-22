#ifndef FUNCTION_H
#define FUNCTION_H

double funtionF(double x, double y) {
	// return (x - 1) * (x - 1) + (y - 1) * (y - 1);
	return 2 * x * (x - 1) + 2 * y * (y - 1);
	// return -4;
	// return 0;
}

double funtionExsol(double x, double y) {
	return x * (x - 1) * y * (y - 1);
}

double funtionU(double x, double y) {
	return (x - 1) * (x - 1) + (y - 1) * (y - 1);
}

#endif