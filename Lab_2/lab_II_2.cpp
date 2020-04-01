/*Розробити функцію, яка переставляє у зворотньому порядку цифри заданого 
довгого цілого числа (наприклад, число 1328 перетвориться на 8231).
З клавіатури ввести масив довгих цілих чисел. Використовуючи розроблену функцію, 
замінити всі числа цього масиву і надрукувати резултат заміни.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 100

void SetValue(int* mass, int max); 
int SwapDigits(int* mass);
void PrintValue(int* mass);

int main() 
{
	system("chcp 1251");
	int arr[N+1]; 
	printf("\nВведіть елементи масиву (цілі числа), максимальна к-сть елементів - %d, для зупинки введіть 0:\n",N);
	SetValue(arr, N);
	if (*arr == 0)
	{
		printf("\nВи не ввели жодного числа в масив!");
		return 0;
	}
	for (int* p = arr; *p != 0; p++) 
	{
		*p = SwapDigits(p);
	}
	printf("\nМасив чисел після перестановки цифр у зворотньому порядку:");
	PrintValue(arr);
}

int SwapDigits(int* chysl) 
{
	int new_chysl = 0;
	do 
	{
		new_chysl = new_chysl * 10 + *chysl % 10;
	} while (*chysl /= 10);
	return new_chysl;
}

void PrintValue(int* mass) 
{
	printf("\n\n-----------------");
	for (int* p = mass; *p != 0; p++) 
	{
		printf("\n%d", *p);
	}
	printf("\n-----------------");
}

void SetValue(int* mass, int max) 
{
	int* p;
	for (p = mass; p - mass < max; p++) 
	{
		scanf_s("%d", p);
		if (*p == 0)
			break;
	}
	*p = 0;
}
