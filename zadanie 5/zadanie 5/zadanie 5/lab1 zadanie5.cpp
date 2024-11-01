#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int   main(void)
{
	int i;
	setlocale(LC_ALL, "RUS");

	struct student
	{
		char famil[20];
		char name[20], facult[20];
		int Nomzach;
	} stud[3];

	for (i = 0; i < 3; i++)
	{
		printf("Введите фамилию студента\n"); scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите имя студента %s\n", stud[i].famil); scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name); scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name); scanf("%d", &stud[i].Nomzach);
	}

	for (i = 0; i < 3; i++)
	{
		printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
			stud[i].facult, stud[i].Nomzach);
	}
}
