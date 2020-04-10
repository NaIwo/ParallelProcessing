#include "pch.h"
#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 1000000000;
double step;

void allNumbers(int number)
{
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	omp_set_num_threads(number); // 8 4 2
	start = clock();
#pragma omp parallel private(x)
	{
		double suma = 0.0;
#pragma omp for
		for (i = 0; i < num_steps; i++)
		{
			x = (i + .5)*step;
			suma += 4.0 / (1. + x * x);
		}
#pragma omp atomic
		sum += suma;
	}

	pi = sum * step;
	stop = clock();

	printf("Proces: %d\n", number);
	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / CLOCKS_PER_SEC));
	printf("\n");
}

int main(int argc, char* argv[])
{

	allNumbers(8);
	allNumbers(4);
	allNumbers(2);
	return 0;
}