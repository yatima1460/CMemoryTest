#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define RAM_BLOCK     1073741824			//1GB
#define VALUE_TO_SET  'C'

void benchmark_memset(unsigned char* ram)
{
	memset(ram, VALUE_TO_SET, RAM_BLOCK);
}

void benchmark_memcpy(unsigned char* ram)
{
	memcpy(ram, ram, RAM_BLOCK);
}

void(*benchmark_function)(unsigned char* ram);

double benchmark(unsigned char* ram)
{
	clock_t start_time = clock();
	benchmark_function(ram);
	clock_t duration = clock() - start_time;
	double time = (double)duration / CLOCKS_PER_SEC;
	return ((RAM_BLOCK) / (1024 * 1024 * 1024) / (time));
}

int main()
{
	printf("CMemoryTest v0.1.0\n\n");
	unsigned char* ram = malloc(RAM_BLOCK);
	if (ram == NULL)
	{
		fprintf(stderr, "Can't allocate ram block");
		abort();
	}
	benchmark_function = benchmark_memset;
	printf("Sequential Write:\t%lf GB/s\n", benchmark(ram));
	benchmark_function = benchmark_memcpy;
	printf("Sequential Read:\t%lf GB/s\n\n", benchmark(ram));
	free(ram);
	return 0;
}

