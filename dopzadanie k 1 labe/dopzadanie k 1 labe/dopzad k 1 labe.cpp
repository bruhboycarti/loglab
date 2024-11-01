#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	int SIZE = 0, summ = 0;
	printf("Input size\n");
	scanf("%d", &SIZE);
	int* mass = (int*)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++)
		printf("%d ", i * 7 - 3);
	free(mass);
	printf("\n\n\n");
	int** a = (int**)malloc(SIZE * sizeof(int*));

	for (int i = 0; i < SIZE; i++)
	{
		a[i] = (int*)malloc(SIZE * sizeof(int));

	}
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = rand() % 100;
	/*вывод массива на экран*/
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%3d ", a[i][j]);
		printf("\n");
	}
	printf("\n");
	/*вывод summ stolb*/
	for (int k = 0; k < 3; k++)
	{
		summ = 0;
		for (int i = 0; i < 5; i++)
			for (int j = k; j < 3; j += 3)
				summ += a[i][j];
		printf("Summ %d : %d\n", k + 1, summ);
	}
	return 0;
}