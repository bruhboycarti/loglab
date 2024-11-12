#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
struct node
{
	char inf[256];  // полезная информация
	int prior;
	struct node* next; // ссылка на следующий элемент 
};
struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
char specchar = '+';
int g = 0;

int spstore();
void review(void), del(char* name);
char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента
struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int num = 0;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);

	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	fflush(stdin);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	printf("Введите приоритет объекта: \n");   // вводим данные
	scanf("%d", &num);
	fflush(stdin);

	p->prior = num;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
int spstore()
{
	struct node* p = NULL;
	struct node* x = NULL;
	struct node* n = NULL;
	struct node* struc = head;
	p = get_struct();
	fflush(stdin);
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец 
	{
		while (struc)
		{
			n = struc->next;
			if ((struc->prior < p->prior) && (n == NULL)) {
				struc->next = p;
				last = p;
				break;
			}
			else if ((struc->prior > p->prior)) {
				p->next = struc;
				if (x != NULL)
				{
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
	printf("Продолжаем ввод? 1/0 \n");
	scanf(" %c", &specchar);
	getchar();
	if (specchar == '1') {

		g = 1;
	}
	else {
		g = 0;
	}

	return (g);
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, Приоритет - %d \n", struc->inf, struc->prior);
		struc = struc->next;
	}
	return;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	spstore();

	while (g == 1) {
		g = spstore();
	}
	review();

}




//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE  
//#define _CRT_NONSTDC_NO_DEPRECATE
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <Windows.h>
//struct node
//{
//	char inf[256];  // полезная информация
//	struct node* next; // ссылка на следующий элемент 
//};
//struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
//char specchar;
//int g = 0;
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
//	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
//	{
//		printf("Ошибка при распределении памяти\n");
//		exit(1);
//	}
//	printf("Введите название объекта: \n");   // вводим данные
//	scanf("%s", s);
//	if (*s == 0)
//	{
//		printf("Запись не была произведена\n");
//		return NULL;
//	}
//	strcpy(p->inf, s);
//	p->next = NULL;
//	return p;		// возвращаем указатель на созданный элемент
//}
///* Последовательное добавление в список элемента (в конец)*/
//int spstore()
//{
//	struct node* p = NULL;
//	p = get_struct();
//	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
//	{
//		head = p;
//		last = p;
//	}
//	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
//	{
//		last->next = p;//голова не меняется, все в конец(FIFO)
//		last = p;
//	}
//	printf("Продолжаем ввод? 1/0 \n");
//	scanf_s(" %c", &specchar);
//	getchar();
//	if (specchar == '1') {
//		g = 1;
//	}
//	else {
//		g = 0;
//	}
//	return (g);
//}
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
//		printf("Имя - %s \n", struc->inf);
//		struc = struc->next;
//	}
//	return;
//}
//int main() {
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	spstore();
//	while (g == 1) {
//		g = spstore();
//	}
//	review();
//}