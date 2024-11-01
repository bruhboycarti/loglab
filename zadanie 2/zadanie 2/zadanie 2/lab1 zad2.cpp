#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "rus");
    int i, mas[10]{};
    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        mas[i] = rand() % 100;
        printf("%d ", mas[i]);
    }
    return(0);
}