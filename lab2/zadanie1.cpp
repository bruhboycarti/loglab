#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <locale.h>

#define NUM_SIZES 7 
const int SIZES[NUM_SIZES] = { 100 ,200, 400, 1000, 2000, 4000, 10000 };

int main()
{	
	setlocale(LC_ALL, "Rus");

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	printf("Размер\tВремя выполнения (мс)\n");
	printf("---------------------------\n");

	for (int sizeIndex = 0; sizeIndex < NUM_SIZES; sizeIndex++)
	{
		int SIZE = SIZES[sizeIndex];
		clock_t start, end; // объявляем переменные для определения времени выполнения 
		double cpu_time_used;

		int i, j, r;
		int** a = (int**)malloc(SIZE * sizeof(int*));
		int** b = (int**)malloc(SIZE * sizeof(int*));
		int** c = (int**)malloc(SIZE * sizeof(int*));

		for (i = 0; i < SIZE; i++)
		{
			a[i] = (int*)malloc(SIZE * sizeof(int));
			b[i] = (int*)malloc(SIZE * sizeof(int));
			c[i] = (int*)malloc(SIZE * sizeof(int));
		}

		// Запускаем таймер 


		srand(time(NULL)); // инициализируем параметры генератора случайных чисел 
		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами 
				b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами 
			}
		}

		start = clock();

		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				int elem_c = 0;
				for (r = 0; r < SIZE; r++)
				{
					elem_c += a[i][r] * b[r][j]; // считаем элемент результата 
				}
				c[i][j] = elem_c;
			}
		}

		// Заканчиваем таймер 
		end = clock();
		cpu_time_used = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; // переводим время в миллисекунды 

		// Вывод времени выполнения 
		printf("%d\t%f\n", SIZE, cpu_time_used);

		// Освобождаем память 
		for (i = 0; i < SIZE; i++)
		{
			free(a[i]);
			free(b[i]);
			free(c[i]);
		}
		free(a);
		free(b);
		free(c);
	}

	return 0;
}