#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "rus");
    int i, n, * mas;
    printf("Введите размер массива: ");
    scanf("%d", &n);
    srand(time(NULL));
    mas = (int*)malloc(n * sizeof(int));
    printf(" massiv: ");
    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        printf("%d ", mas[i]);
    }
    free(mas);
    return(0);
}


