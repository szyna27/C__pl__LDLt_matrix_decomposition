#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
FILE* fr, * fw;
extern void error(int, char*);
extern double* mem(int);
extern double** memmatrix(int n);
extern void freematrix(double**, int);
extern void readmatrix(FILE*, double**, int);
extern void writematrix(FILE*, double**, int, char);
extern void readvector(FILE*, double*, int);
extern void writevector(FILE*, double*, int, char);
extern void LDLt(double**, double*, double**, int);
extern void solve(double**, double*, double*, int, double*);

int main()
{
	double **A, *x, *b, **L, *D;
	int n, i, j;

	if (!(fr = fopen("dane", "r")))
		error(2, "dane");

	if(fscanf(fr, "%d", &n) != 1)
		error(1, "size");
	
	x = mem(n);
	b = mem(n);
	D = mem(n);
	A = memmatrix(n);
	L = memmatrix(n);

	readmatrix(fr, A, n);
	readvector(fr, b, n);
	fclose(fr);
	fr = NULL;
	
	if (!(fw = fopen("wynik", "w")))
		error(2, "wynik");

	printf("Dane:\n");
	writevector(fw, b, n, 'b');
	writematrix(fw, A, n, 'A');

	LDLt(L, D, A, n);
	freematrix(A, n);

	printf("\nRozklad:\n");
	writematrix(fw, L, n, 'L');
	writevector(fw, D, n, 'D');

	solve(L, D, b, n, x);
	freematrix(L, n);
	free(b);

	printf("\nWynik:\n");
	writevector(fw, x, n, 'x');
	free(x);
	fclose(fw);
	fw = NULL;

	return 0;
}