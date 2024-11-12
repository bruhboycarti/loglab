//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE  
//#define _CRT_NONSTDC_NO_DEPRECATE
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <Windows.h>
//struct node
//{
//	char inf[256]; 
//	int prior;
//	struct node* next; // ссылка на следующий элемент 
//};
//struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
//char specchar = '+';
//int g = 0;
//
//int spstore();
//void review(void), del(char* name);
//char find_el[256];
//struct node* find(char* name); // функция нахождения элемента
//struct node* get_struct(void); // функция создания элемента
//struct node* get_struct(void)
//{
//	struct node* p = NULL;
//	char s[256];
//	int num = 0;
//
//	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
//	{
//		printf("Ошибка при распределении памяти\n");
//		exit(1);
//
//	}
//
//	printf("Введите название объекта: \n");   // вводим данные
//	scanf("%s", s);
//	fflush(stdin);
//	if (*s == 0)
//	{
//		printf("Запись не была произведена\n");
//		return NULL;
//	}
//	strcpy(p->inf, s);
//
//	printf("Введите приоритет объекта: \n");   // вводим данные
//	scanf("%d", &num);
//	fflush(stdin);
//
//	p->prior = num;
//
//	p->next = NULL;
//
//	return p;		// возвращаем указатель на созданный элемент
//}
//
///* Последовательное добавление в список элемента (в конец)*/
//int spstore()
//{
//	struct node* p = NULL;
//	struct node* x = NULL;
//	struct node* n = NULL;
//	struct node* struc = head;
//	p = get_struct();
//	fflush(stdin);
//	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
//	{
//		head = p;
//		last = p;
//	}
//	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец 
//	{
//		while (struc)
//		{
//			n = struc->next;
//			if ((struc->prior < p->prior) && (n == NULL)) {
//				struc->next = p;
//				last = p;
//				break;
//			}
//			else if ((struc->prior > p->prior)) {
//				p->next = struc;
//				if (x != NULL)
//				{
//					x->next = p;
//				}
//				if (struc == head) {
//					head = p;
//				}
//				break;
//			}
//			else if ((struc->prior <= p->prior)) {
//				x = struc;
//				struc = struc->next;
//			}
//		}
//	}
//	printf("Продолжаем ввод? да/нет \n");
//	scanf(" %c", &specchar);
//	getchar();
//	if (specchar == '1') {
//
//		g = 1;
//	}
//	else {
//		g = 0;
//	}
//
//	return (g);
//}
//
//
///* Просмотр содержимого списка. */
//void review(void)
//{
//	struct node* struc = head;
//	if (head == NULL)
//	{
//		printf("Список пуст\n");
//	}
//	while (struc)
//	{
//		printf("Имя - %s, Приоритет - %d \n", struc->inf, struc->prior);
//		struc = struc->next;
//	}
//	return;
//}
//int main() {
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	spstore();
//
//	while (g == 1) {
//		g = spstore();
//	}
//	review();
//
//}



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// Структура для элемента очереди
struct node {
    char inf[256];        // информация в узле
    struct node* next;    // указатель на следующий элемент
};

// Указатели на начало и конец очереди
struct node* front = NULL;    // указатель на начало очереди (откуда удаляем)
struct node* rear = NULL;     // указатель на конец очереди (куда добавляем)

// Функция создания нового элемента
struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите данные: \n");
    scanf("%s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;

    return p;
}

// Функция добавления элемента в очередь (enqueue)
void enqueue(void) {
    struct node* p = get_struct();

    if (p == NULL) return;

    // Если очередь пуста
    if (front == NULL) {
        front = rear = p;
    }
    // Добавляем элемент в конец очереди
    else {
        rear->next = p;
        rear = p;
    }
    printf("Элемент добавлен в очередь\n");
}

// Функция удаления элемента из очереди (dequeue)
void dequeue(void) {
    if (front == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = front;
    printf("Удален элемент: %s\n", front->inf);

    front = front->next;

    // Если удалили последний элемент
    if (front == NULL) {
        rear = NULL;
    }

    free(temp);
}

// Функция просмотра очереди
void review(void) {
    struct node* temp = front;

    if (front == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Содержимое очереди:\n");
    while (temp != NULL) {
        printf("%s\n", temp->inf);
        temp = temp->next;
    }
}

// Функция проверки, пуста ли очередь
int is_empty(void) {
    return front == NULL;
}

// Функция получения первого элемента без его удаления
void peek(void) {
    if (front == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    printf("Первый элемент в очереди: %s\n", front->inf);
}

int main() {
       int choice;
       SetConsoleCP(1251);
           SetConsoleOutputCP(1251);

    while (1) {
        printf("\n1. Добавить элемент в очередь\n");
        printf("2. Удалить элемент из очереди\n");
        printf("3. Показать очередь\n");
        printf("4. Показать первый элемент\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            review();
            break;
        case 4:
            peek();
            break;
        case 5:
            // Освобождаем память перед выходом
            while (!is_empty()) {
                dequeue();
            }
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}