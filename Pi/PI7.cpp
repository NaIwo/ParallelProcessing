#include "pch.h"
#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])		
{
	volatile double tab[50] = { 0.0 };
	for (int j = 0; j < 49; j++)
	{
		clock_t start, stop;
		double x, pi, sum = 0.0;
		int i;
		step = 1. / (double)num_steps;
		
		start = clock();
		omp_set_num_threads(2);
#pragma omp parallel 
		{
			int num = omp_get_thread_num();
			tab[j + num] = 0.0;
#pragma omp for private(x)
			for (i = 0; i < num_steps; i++)
			{
				x = (i + .5)*step;
				tab[j + num] += 4.0 / (1. + x * x);
			}

#pragma omp atomic
			sum += tab[j + num];
		}
		pi = sum * step;
		stop = clock();
	printf("--------------------START-------------------\n");
	printf("Iteracja: %d\n", j);
	printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / CLOCKS_PER_SEC));
	printf("Indeksy: %d, %d\n", j, j+1);
	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("--------------------STOP-------------------\n\n\n");
	}
	return 0;
}