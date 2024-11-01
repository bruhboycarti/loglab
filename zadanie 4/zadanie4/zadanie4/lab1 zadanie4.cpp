#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h> 
#include <stdlib.h>
#include <time.h>


int main(void)
{
    int** a = (int**)malloc(SIZE * sizeof(int*));

    for (i = 0; i < SIZE; i++)
    {
        a[i] = (int*)malloc(SIZE * sizeof(int));
    }
    int  summ, Arr[5][3]{};
    srand(time(NULL));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            Arr[i][j] = rand() % 100;
    /*вывод массива на экран*/
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%3d ", Arr[i][j]);
        printf("\n");
    }
    printf("\n");
    /*вывод summ stolb*/
    for (int k = 0; k < 3; k++)
    {
        summ = 0;
        for (int i = 0; i < 5; i++)
            for (int j = k; j < 3; j += 3)
                summ += Arr[i][j];
        printf("Summ %d : %d\n", k + 1, summ);
    }
    return 0;
}



