#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
extern void error(int, char*);
extern double* mem(int);

void LDLt(double** L, double* D, double** A, int n) {
	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j <= i; j++) {
			if (i == j) {
				L[i][i] = 1;
				if (!(D[i] = A[i][i])) {
					error(4, "D");
				}
				for (k = 0; k < j; k++)
					D[j] -= L[j][k] * L[j][k] * D[k];
			}
			else {
				L[i][j] = A[i][j];
				for (k = 0; k < j; k++)
					L[i][j] -= L[i][k] * L[j][k] * D[k];
				L[i][j] /= D[j];
			}
		}
}

void solve(double** L, double* D, double* b, int n, double* x) {
	int i, j, k;
	double* y, * z;
	y = mem(n);
	z = mem(n);

	for (i = 0; i < n; i++) {
		y[i] = b[i];
		for (k = 0; k < i; k++)
			y[i] -= L[i][k] * y[k];
	}

	for (i = 0; i < n; i++) {
		z[i] = y[i] / D[i];
	}

	for (i = n - 1; i > -1; i--) {
		x[i] = z[i];
		for (k = i + 1; k < n; k++)
			x[i] -= L[k][i] * x[k];
	}
	free(y);
	free(z);
}