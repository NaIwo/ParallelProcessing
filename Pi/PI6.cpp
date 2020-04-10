#include "pch.h"
#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{

	clock_t start, stop;
	double x, pi;
	int i;
	step = 1. / (double)num_steps;
	omp_set_num_threads(2); // 8 4 2
	volatile double sum[2] = { 0.0 };
	start = clock();

#pragma omp parallel private(x)
	{
		int num = omp_get_thread_num();
#pragma omp for 
		for (i = 0; i < num_steps; i++)
		{
			x = (i + .5)*step;
			sum[num] += 4.0 / (1. + x * x);
		}
	}
	pi = (sum[0] + sum[1]) * step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / CLOCKS_PER_SEC));
	return 0;
}