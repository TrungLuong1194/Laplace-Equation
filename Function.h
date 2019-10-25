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

#endif