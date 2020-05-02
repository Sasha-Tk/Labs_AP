/*У динамічній пам'яті виділити місце для збереження масиву
цілих чисел заданої розміроності. Заповнити цей масив 
випадковими трицифровими числами, в кожному з яких усі три 
цифри різні. Серед елементів масиву не повинно бути однакових. 
Відсортувати згенерований масив за зростанням значень 
елементів і надрукувати його. Релазіувати дві функції: 
1) длі перевірки цифр заданого трицифрового числа; 
2) для перевірки, чи входить у масив вказаної довжини 
задане ціле число.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30

bool CheckArray(int* arrey, int k, int digit);
bool CheckFigures(int digit);
void SetAmount(int* n);
void SetArray(int* array, int n);
void fPrintArray(FILE* f_name, int* array, int n);
bool OpenFile(FILE** pointer, const char* f_name, const char* mode);

int main(void)
{
	system("chcp 1251");
	srand((unsigned)time(NULL));
	int n;
	char* f_name;
	FILE* file;
	f_name = (char*)malloc(N * sizeof(char));
	printf("\nВведіть ім'я файлу: ");
	gets_s(f_name, N);
	if (!OpenFile(&file, f_name, "w"))
	{
		return 0;
	}
	SetAmount(&n);
	int* array = (int*)malloc(sizeof(int) * n);
	SetArray(array, n);
	fPrintArray(file, array, n);
	printf("\n%d унікальних трьохзначних чисел записано у файл %s\n", n, f_name);
	_fcloseall();
	free(array);
	free(f_name);
	return 0;
}

bool CheckArray(int* arrey, int k, int digit)
{
	for (int i = 0; i < k; i++)
	{
		if (arrey[i] == digit)
		{
			return true;
		}
	}
	return false;
}

bool CheckFigures(int digit)
{
	int figures[3], i = 0;
	do {
		figures[i] = digit % 10;
		if (CheckArray(figures, i, figures[i]))
		{
			return false;
		}
		i++;
	} while (digit /= 10);
	return true;
}

void SetAmount(int* n)
{
	printf("\nВведіть кількість елементів масиву: ");
	scanf_s("%d", n);
	while (*n <= 0)
	{
		if (*n <= 0)
		{
			printf("\nКількість елементів має бути > 0!\n"
				"Повторіть спробу: ");
		}
		scanf_s("%d", n);
	}
	if (*n > 648)
	{
		printf("\nМаксимальна кількість унікальних елементів 648!");
		*n = 648;
	}
}

void SetArray(int* array, int n)
{
	int new_digit;
	for (int i = 0; i < n;)
	{
		new_digit = rand() % 1000;
		if (new_digit < 99 || CheckFigures(new_digit) == false || CheckArray(array, i, new_digit) == true)
		{
			continue;
		}
		array[i] = new_digit;
		i++;
	}
}

void fPrintArray(FILE* f_name, int* array, int n)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(f_name, "%d) %d\n", i + 1, array[i]);
	}
}

bool OpenFile(FILE** pointer, const char* f_name, const char* mode)
{
	*pointer = fopen(f_name, mode);
	if (*pointer == NULL)
	{
		printf("\nНе вдалось відкрити файл: %s\n", f_name);
		return false;
	}
	else
	{
		printf("\nУспішно відкрито файл %s\n", f_name);
		return true;
	}
}