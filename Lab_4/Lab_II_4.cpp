/*Розробити функцію, яка міняє місцями відповідні за номером елементи двох векторів
цілих чисел однакової довжини. З клавіатури ввести цілочислову матрицю.
На основі розробленої функції переставити рядкі введеної матриці у зворотньому порядку.
Надрукувати матрицю після переставлення елементів.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 4
#define S 3

int ChangeMatrix(int(*upper)[N], int(*lover)[N], int smb); //функція перестановки рядків матриці
void ChangeVector_I(int* v_1, int* v_2, int k); //ітераційна функція, яка міняє місцями відповідні елементи двох векторів
void ChangeVector_R(int* v_1, int* v_2, int k); //рекурсивна функція, яка міняє місцями відповідні елементи двох векторів
void swap(int* a, int* b); //функція обміну значеннями між двома змінними
void GetVector(int* v, int k); //функція заповнення значеннями векторів
void GetMatrix(int(*matrix)[N]); //функція заповнення значеннями матриці 
void PrintVector(int* v, int size); //функція друкування вектора
void PrintMatrix(int(*matrix)[N]); //друкування матриці

int main(void)
{
	system("chcp 1251");
	int v_1[N], v_2[N];
	int matrix[S][N];
	printf("\nВведіть v_1 з кількістю елементів %d: ", N);
	GetVector(v_1, N);
	printf("\nВведіть v_2 з кількістю елементів %d: ", N);
	GetVector(v_2, N);
	printf("\nv_1");
	PrintVector(v_1, N);
	printf("\nv_2");
	PrintVector(v_2, N);

	printf("\n----------Ітераційна версія----------");
	ChangeVector_I(v_1, v_2, N); //виклик функції для ітераційної перестановки елементів векторів
	printf("\nПісля заміни елементів v_1 ");
	PrintVector(v_1, N);
	printf("\nПісля заміни елементів v_2 ");
	PrintVector(v_2, N);

	printf("\n----------Рекурсивна версія----------");
	ChangeVector_R(v_1, v_2, N); //виклик функції для рекурсивної перестановки елементів векторів
	printf("\nПісля заміни елементів v_1");
	PrintVector(v_1, N);
	printf("\nПісля заміни елементів v_2");
	PrintVector(v_2, N);

	printf("\n\nВведіть елементи матриці %dx%d для ітераційної перестановки:\n", S, N);
	GetMatrix(matrix);
	printf("\nМатриця після перестановки:\n");
	ChangeMatrix(&matrix[0], &matrix[S - 1], 'I'); //виклик функції для ітераційної перестановки рядків матриці
	PrintMatrix(matrix);

	printf("\n\nВведіть елементи матриці %dx%d для рекурсивної перестановки:\n", S, N);
	GetMatrix(matrix);
	printf("\nМатриця після перестановки:\n");
	ChangeMatrix(&matrix[0], &matrix[S - 1], 'R');//виклик функції для рекурсивної перестановки рядків матриці
	PrintMatrix(matrix);
	return 0;
}

int ChangeMatrix(int(*upper)[N], int(*lover)[N], int smb) //функція перестановки рядків матриці
{
	int(*p_u)[N] = upper, (*p_l)[N] = lover;
	if (smb == 'I') {
		while (p_u < p_l)
		{
			ChangeVector_I(*p_u, *p_l, N);
			p_u++;
			p_l--;
		}
		return 0;
	}
	if (smb == 'R')
	{
		while (p_u < p_l)
		{
			ChangeVector_R(*p_u, *p_l, N);
			p_u++;
			p_l--;
		}
		return 0;
	}
	return -1;
}

void ChangeVector_I(int* v_1, int* v_2, int k) //ітераційна функція, яка міняє місцями відповідні елементи двох векторів
{
	int* p_1 = v_1, * p_2 = v_2;
	for (int i = 0; i < k; i++)
	{
		swap(p_1++, p_2++);
	}
}

void ChangeVector_R(int* v_1, int* v_2, int k) //рекурсивна функція, яка міняє місцями відповідні елементи двох векторів
{
	int* p_1 = v_1, * p_2 = v_2;
	if (p_1 - v_1 > k - 1) return;
	swap(p_1, p_2);
	ChangeVector_R(p_1 + 1, p_2 + 1, k - 1);
}

void swap(int* a, int* b) //функція обміну значеннями між двома змінними
{
	int c = *a;
	*a = *b;
	*b = c;
}

void GetVector(int* v, int k) //функція заповнення значеннями векторів
{
	int* p;
	for (p = v; p - v < k; p++)
	{
		scanf_s("%d", p);
	}
}

void GetMatrix(int(*matrix)[N]) //функція заповнення значеннями матриці 
{
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < N; j++)
			scanf_s("%d", &matrix[i][j]);
	}
}

void PrintVector(int* v, int size) //функція друкування вектора
{
	int* p;
	printf(" = (");
	for (p = v; p - v < size; p++)
	{
		printf("%d", *p);
		if (p - v < size - 1)
			printf(", ");
	}
	printf(");\n");
}

void PrintMatrix(int(*matrix)[N]) //друкування матриці
{
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < N; j++) {

			printf("%d", matrix[i][j]);
			if (j < N - 1)
				printf(", ");
		}
		printf("\n");
	}
}