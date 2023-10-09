#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
extern void error(int, char*);

double* mem(int n) {
	double* p;
	if (p = (double*)malloc(sizeof(double) * n))
		return p;
	else
		error(3, "Tablica");
}

double** memmatrix(int n) {
	double** p;
	if (!(p = (double**)malloc(sizeof(double*) * n))) {
		error(3, "Tablica");
	}
	for (int i = 0; i < n; i++)
		p[i] = mem(i + 1);
	return p;
}

void readvector(FILE* f, double* v, int n) {	
	int i;
	for (i = 0; i < n; i++) {
		if (fscanf(f, "%lf", &v[i]) != 1)
			error(1, "vector");
	}
}

void writevector(FILE* f, double* v, int n, char c) {
	int i;
	fprintf(f, "%c:\n", c);
	printf("%c:\n", c);
	for (i = 0; i < n; i++) {
		fprintf(f, "%lf ", v[i]);
		printf("%lf ", v[i]);
	}
	fprintf(f, "\n");
	printf("\n");
}

void readmatrix(FILE* f, double** ma, int n){
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j <= i; j++){
			if (fscanf(f, "%lf", &ma[i][j]) != 1)
				error(1, "matrix");
		}
}

void writematrix(FILE* f, double** ma, int n, char c) {
	int i, j;
	fprintf(f, "%c:\n", c);
	printf("%c:\n", c);
	for (i = 0; i < n; i++) {
		for (j = 0; j <= i; j++) {
			fprintf(f, "%lf ", ma[i][j]);
			printf("%lf ", ma[i][j]);
		}
		fprintf(f, "\n");
		printf("\n");
	}
}

void freematrix(double** ma, int n) {
	if (ma) {
		for (int i = 0; i < n; i++)
			if (ma[i]) free(ma[i]);
		free(ma);
		ma = NULL;
	}
}