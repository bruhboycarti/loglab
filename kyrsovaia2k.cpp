#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// Стартовая заставка с информацией о проекте
int z1() {
    system("cls");
    setlocale(LC_ALL, "Rus");
    char title[] = "   Реализация поиска независимых множеств вершин графа\n";
    char title2[] = "Выполнил студент группы: 23ВВВ2\n";
    char title3[] = " Попков С.А\n";
    int length = strlen(title);
    int length2 = strlen(title2);
    int length3 = strlen(title3);

    int x, y;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // рассчет отступа для каждой строки
    int x_title = (console_width - length) / 2;
    int x_title2 = (console_width - length2) / 2;
    int x_title3 = (console_width - length3) / 2;
    y = console_height / 2;

    //  заголовок по центру
    for (int i = 0; i < y - 2; i++)  // Добавляем пустые строки чтобы был ближе к центру
        printf("\n");

    for (int i = 0; i < x_title; i++)
        printf(" ");
    for (int j = 0; j < length; j++) {
        printf("%c", title[j]);
        Sleep(20);
    }
    Sleep(200);

    //  ФИО по центру
    for (int i = 0; i < x_title2; i++)
        printf(" ");
    for (int m = 0; m < length2; m++) {
        printf("%c", title2[m]);
        Sleep(60);
    }
    Sleep(600);

    // информация о группе и курсе по центру
    for (int l = 0; l < x_title3; l++)
        printf(" ");
    for (int n = 0; n < length3; n++) {
        printf("%c", title3[n]);
        Sleep(60);
    }
    Sleep(500);
    system("cls");
    return 0;
}

void showMenu() {
    printf("1. Ввести размер графа\n");
    printf("2. Заполнить граф вручную\n");
    printf("3. Заполнить граф случайными числами\n");
    printf("4. Найти независимые множества и вывести в консоль\n");
    printf("5. Сохранить результат в файл\n");
    printf("6. Показать матрицу графа\n");
    printf("7. Выйти\n");
}

// функция для создания пустой матрицы смежности
int** createGraph(int size) {
    int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            graph[i][j] = 0; // инициализация нулями
        }
    }
    return graph;
}

// функция для ручного ввода графа
void inputGraph(int** graph, int size) {
    printf("Введите матрицу смежности графа (только 0 и 1):\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < j) { // проверяем, чтобы вводить только верхнюю часть матрицы
                int value;
                do {
                    printf("Элемент [%d][%d]: ", i, j);
                    scanf_s("%d", &value);
                    if (value != 0 && value != 1) {
                        printf("Ошибка: можно вводить только 0 или 1.\n");
                    }
                } while (value != 0 && value != 1);

                // Устанавливаем значение симметрично для неориентированного графа
                graph[i][j] = value;
                graph[j][i] = value;
            }
            else if (i == j) {
                graph[i][j] = 0; // Нет петель на вершину
            }
        }
    }
}

// функция для заполнения графа случайными числами (только 0 и 1)
void randomGraph(int** graph, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                graph[i][j] = rand() % 2; // случайное значение 0 или 1
               // graph[j][i] = graph[i][j]; // обеспечиваем симметричность
            }
            else {
                graph[i][j] = 0; // нет петель на вершину
            }
        }
    }
    printf("Граф успешно заполнен случайными числами.\n");
}

// функция для вывода матрицы смежности
void printGraph(int** graph, int size) {
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Функция для поиска всех независимых множеств
void findAllIndependentSets(int** graph, int size, int* currentSet, int currentSize, int index, FILE* file) {
    if (index == size) {
        if (currentSize > 0) {
            fprintf(file, "{ ");
            for (int i = 0; i < currentSize; i++) {
                fprintf(file, "%d ", currentSet[i] + 1); // +1 для удобства отображения
            }
            fprintf(file, "}\n");
        }
        return;
    }

    // Включаем текущую вершину в независимое множество
    int canInclude = 1;
    for (int i = 0; i < currentSize; i++) {
        if (graph[currentSet[i]][index] == 1) {
            canInclude = 0;
            break;
        }
    }
    if (canInclude) {
        currentSet[currentSize] = index;
        findAllIndependentSets(graph, size, currentSet, currentSize + 1, index + 1, file);
    }
    // Исключаем текущую вершину из независимого множества
    findAllIndependentSets(graph, size, currentSet, currentSize, index + 1, file);
}

// Функция для поиска независимых множеств и записи их в файл
void findIndependentSetsToFile(int** graph, int size, FILE* file) {
    fprintf(file, "Множества независимых вершин:\n"); // Заголовок перед выводом множеств

    // Динамическое выделение памяти для currentSet
    int* currentSet = (int*)malloc(size * sizeof(int));
    if (currentSet == NULL) {
        printf("Ошибка: не удалось выделить память для currentSet.\n");
        return;
    }

    // Поиск независимых множеств
    findAllIndependentSets(graph, size, currentSet, 0, 0, file);

    // Освобождение памяти
    free(currentSet);
}

// сохранение результатов в файл
void saveResultsToFile(int** graph, int size) {
    FILE* file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    // сохраняем матрицу смежности
    fprintf(file, "Матрица смежности графа:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", graph[i][j]);
        }
        fprintf(file, "\n");
    }

    // запускаем поиск независимых множеств и сохраняем в файл
    findIndependentSetsToFile(graph, size, file);

    // закрываем файл
    fclose(file);
    printf("Все независимые множества сохранены в файл result.txt\n");
}

// основная функция
int main() {
    int size = 0;
    int** graph = NULL;
    int choice;

    z1(); // запуск заставки

    while (1) {
        showMenu();
        printf("Введите ваш выбор: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите размер графа: ");
            scanf_s("%d", &size);
            if (size < 1) {
                printf("Размер графа должен быть больше 0.\n");
                return 1;
            }
            else {
                graph = createGraph(size); // Создаем граф
            }
            break;
        case 2:
            if (size == 0) {
                printf("Сначала задайте размер графа!\n");
            }
            else {
                inputGraph(graph, size); // Заполняем граф вручную
            }
            break;
        case 3:
            if (size == 0) {
                printf("Сначала задайте размер графа!\n");
            }
            else {
                randomGraph(graph, size); // Заполняем граф случайными числами
            }
            break;
        case 4:
            if (size == 0) {
                printf("Сначала заполните граф!\n");
            }
            else {
    printf("Независимые множества:\n");
    
    // Запрашиваем у пользователя количество вершин
    int numVertices;
    printf("Введите количество вершин: ");
    scanf("%d", &numVertices);

    // Динамическое выделение памяти для массива индексов вершин текущего независимого множества
    int* currentSet = (int*)malloc(numVertices * sizeof(int));
    if (currentSet == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1; // Завершение программы в случае ошибки
    }

    findAllIndependentSets(graph, size, currentSet, 0, 0, stdout); // Выводим в консоль

    // Освобождение выделенной памяти
    free(currentSet);
}
            break;
        case 5:
            if (size == 0) {
                printf("Сначала найдите независимые вершины!\n");
            }
            else {
                saveResultsToFile(graph, size); // Сохраняем результаты в файл
            }
            break;
        case 6:
            if (size == 0) {
                printf("Сначала создайте матрицу!\n");
            }
            else {
                printGraph(graph, size); // Показываем матрицу графа
            }
            break;
        case 7:
            for (int i = 0; i < size; i++)
                free(graph[i]); // Освобождаем память
            free(graph);
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }
    }
    return 0;
}

