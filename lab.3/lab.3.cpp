#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h> 

void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;



    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}
int compare(const void* x1, const void* x2)   /*функция сравнения элементов массива*/
{
    return (*(int*)x1 - *(int*)x2);              /* <0	elem1 меньше elem2,  =0	elem1 эквивалентен elem2,   >0	elem1 больше elem2*/
}

int main() {
    const int count = 100000;
    double tim1, tim2, tim3;
    clock_t start, end; // объявляем переменные для определения времени выполнени
    /*int b[count], c[count], d[count];*/
    int* g = (int*)malloc(count * sizeof(int));
    int* b = (int*)malloc(count * sizeof(int));
    int* c = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count / 2; i++) {
        b[i] = i;
    }
    for (int i = count / 2; i < count; i++) {
        b[i] = b[49999] - 1;
    }
    for (int i = 0; i < count; i++) {
        c[i] = b[i];
    }
    for (int i = 0; i < count; i++) {
        g[i] = b[i];
    }

    //SHELL
    start = clock();
    shell(b, count);
    end = clock();
    tim1 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("shell");
    printf("\n%lf", tim1);

    //QS
    start = clock();
    qs(c, 0, count - 1);
    end = clock();
    tim2 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\nqs");
    printf("\n%lf", tim2);

    //QSORT
    start = clock();
    qsort(g, count, sizeof(int), compare);
    end = clock();
    tim3 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\nqsort");
    printf("\n%lf", tim3);

    return(0);

}
