#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>

int main(void)
{
    int a[10];
    int min = 33000;
    int max = 0;

    for (int i = 0; i < 10; i++) { // 2 задание
        a[i] = rand();
    }

    for (int i = 0; i < 10; i++) { // 1 задание
        if (a[i] > max) {
            max = a[i];
        }
        if (a[i] < min) {
            min = a[i];
        }
    }

    printf("minimum = %d\n", min);
    printf("maximum = %d\n", max);

    return 0;
}