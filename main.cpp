#include <stdio.h>
#include <math.h>
#include "rk4.h"

void rhs_fun(double t, double* X, double* F);

double g = 9.8, rho = 1.2;
double m, S, C;

void main()
{
	double z0;
	double v0;
	double h = 0.01;
	double t_max = 10;

	do {
		printf("Podaj polozenie poczatkowe\nz0=");
		scanf("%lf", &z0);

	} while (z0 <= 0);

	printf("Podaj predkosc poczatkowa\nv0=");
	scanf("%lf", &v0);

	printf("Podaj mase, powierzchnie oraz wspolczynnik oporu kuli\n");

	do {
		printf("m=");
		scanf("%lf", &m);

	} while (m <= 0);

	do {
		printf("S=");
		scanf("%lf", &S);

	} while (S <= 0);

	do {
		printf("C=");
		scanf("%lf", &C);

	} while (C <= 0);

	FILE* f = fopen("dane.txt", "w");

	double X[2] = { z0, v0 };
	double X1[2];

	fprintf(f,"t \t z \t v \n");
	printf("t \t z \t v \n");

	for (double t = 0; t < t_max; t += h)
	{

		vrk4(t, X, h, 2, rhs_fun, X1);
		fprintf(f, "%lf \t %lf \t %lf \n", t, X[0], X[1]);
		printf("%lf \t %lf \t %lf \n", t, X[0], X[1]);

		for (int i = 0; i < 2; i++)
		{
			X[i] = X1[i];
		}

		if (X[0] <= 0) {
			X[0] = -X[0];
			X[1] = -X[1];
		}
	}

	fclose(f);
}

void rhs_fun(double t, double* X, double* F)
{
	F[0] = X[1];
	F[1] = -rho / 2 * S * C / m * X[1] * fabs(X[1]) - g;
}
