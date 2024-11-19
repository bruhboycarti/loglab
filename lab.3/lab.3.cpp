#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct node {
    char inf[256];
    int prior;
    struct node* next;
};

struct node* head = NULL, * last = NULL;

// Функция создания элемента
struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];
    int num = 0;

    if ((p = (node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");
    scanf("%s", s);
    fflush(stdin);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    printf("Введите приоритет объекта: \n");
    scanf("%d", &num);
    fflush(stdin);

    p->prior = num;
    p->next = NULL;

    return p;
}

// Добавление элемента с учетом приоритета
void spstore() {
    struct node* p = NULL;
    struct node* x = NULL;
    struct node* n = NULL;
    struct node* struc = head;

    p = get_struct();
    if (p == NULL) return;

    if (head == NULL) {
        head = p;
        last = p;
    }
    else {
        while (struc) {
            n = struc->next;
            if ((struc->prior < p->prior) && (n == NULL)) {
                struc->next = p;
                last = p;
                break;
            }
            else if ((struc->prior > p->prior)) {
                p->next = struc;
                if (x != NULL) {
                    x->next = p;
                }
                if (struc == head) {
                    head = p;
                }
                break;
            }
            else if ((struc->prior <= p->prior)) {
                x = struc;
                struc = struc->next;
            }
        }
    }
    printf("Элемент успешно добавлен\n");
}

// Просмотр содержимого списка
void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    printf("\nСодержимое списка:\n");
    while (struc) {
        printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->prior);
        struc = struc->next;
    }
}

// Поиск элемента по имени
void find(void) {
    char name[256];
    printf("Введите имя для поиска: ");
    scanf("%s", name);

    struct node* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->inf, name) == 0) {
            printf("Найден элемент: Имя - %s, Приоритет - %d\n",
                current->inf, current->prior);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Элемент не найден\n");
    }
}

// Очистка списка
void clear_list(void) {
    struct node* current = head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
    last = NULL;
    printf("Список очищен\n");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        printf("\nМеню\n");
        printf("1. Добавить элемент\n");
        printf("2. Просмотреть список\n");
        printf("3. Найти элемент\n");
        printf("4. Очистить список\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
        case 1:
            spstore();
            break;
        case 2:
            review();
            break;
        case 3:
            find();
            break;
        case 4:
            clear_list();
            break;
        case 0:
            printf("Программа завершена\n");
            clear_list(); // Очищаем память перед выходом
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}


//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <Windows.h>
//
//// Структура для элемента очереди
//struct node {
//    char inf[256];        
//    struct node* next;    // указатель на следующий элемент
//};
//
//// Указатели на начало и конец очереди
//struct node* front = NULL;    // указатель на начало очереди (откуда удаляем)
//struct node* rear = NULL;     // указатель на конец очереди (куда добавляем)
//
//// Функция создания нового элемента
//struct node* get_struct(void) {
//    struct node* p = NULL;
//    char s[256];
//
//    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
//        printf("Ошибка при распределении памяти\n");
//        exit(1);
//    }
//
//    printf("Введите данные: \n");
//    scanf("%s", s);
//    if (*s == 0) {
//        printf("Запись не была произведена\n");
//        free(p);
//        return NULL;
//    }
//    strcpy(p->inf, s);
//    p->next = NULL;
//
//    return p;
//}
//
//// Функция добавления элемента в очередь (enqueue)
//void enqueue(void) {
//    struct node* p = get_struct();
//
//    if (p == NULL) return;
//
//    // Если очередь пуста
//    if (front == NULL) {
//        front = rear = p;
//    }
//    // Добавляем элемент в конец очереди
//    else {
//        rear->next = p;
//        rear = p;
//    }
//    printf("Элемент добавлен в очередь\n");
//}
//
//// Функция удаления элемента из очереди (dequeue)
//void dequeue(void) {
//    if (front == NULL) {
//        printf("Очередь пуста\n");
//        return;
//    }
//
//    struct node* temp = front;
//    printf("Удален элемент: %s\n", front->inf);
//
//    front = front->next;
//
//    // Если удалили последний элемент
//    if (front == NULL) {
//        rear = NULL;
//    }
//
//    free(temp);
//}
//
//// Функция просмотра очереди
//void review(void) {
//    struct node* temp = front;
//
//    if (front == NULL) {
//        printf("Очередь пуста\n");
//        return;
//    }
//
//    printf("Содержимое очереди:\n");
//    while (temp != NULL) {
//        printf("%s\n", temp->inf);
//        temp = temp->next;
//    }
//}
//
//// Функция проверки, пуста ли очередь
//int is_empty(void) {
//    return front == NULL;
//}
//
//// Функция получения первого элемента без его удаления
//void peek(void) {
//    if (front == NULL) {
//        printf("Очередь пуста\n");
//        return;
//    }
//    printf("Первый элемент в очереди: %s\n", front->inf);
//}
//
//int main() {
//       int choice;
//       SetConsoleCP(1251);
//           SetConsoleOutputCP(1251);
//
//    while (1) {
//        printf("\n1. Добавить элемент в очередь\n");
//        printf("2. Удалить элемент из очереди\n");
//        printf("3. Показать очередь\n");
//        printf("4. Показать первый элемент\n");
//        printf("5. Выход\n");
//        printf("Выберите действие: ");
//        scanf("%d", &choice);
//
//        switch (choice) {
//        case 1:
//            enqueue();
//            break;
//        case 2:
//            dequeue();
//            break;
//        case 3:
//            review();
//            break;
//        case 4:
//            peek();
//            break;
//        case 5:
//            // Освобождаем память перед выходом
//            while (!is_empty()) {
//                dequeue();
//            }
//            return 0;
//        default:
//            printf("Неверный выбор\n");
//        }
//    }
//
//    return 0;
//}