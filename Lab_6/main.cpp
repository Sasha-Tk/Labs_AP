/*З клавіатури ввести набір цілочислових даних, які задають координати
(x,y,z) вершин просторового багатокутника. Роздрукувати введені дані
у вигляді таблиці, відсортувавши їх за зростанням координати х.
Визначити, чи є підгрупи точок, що лежать на одній горизонтальній
площині (мають однакову координату z).
Якщо так, то визначити найчисленнішу групу.*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

	extern int  coord_of_max_group;
	static int k_vved = 0;

int main(void) {

	system("chcp 1251");
	Point point[N];
	int max_group = 0; 
	k_vved = Entering(point);
	if (k_vved == 0) {
		printf("\nВи не ввели жодної точки!\n");
		return 0;
	}
	puts("\nДо сортування");
	outPoint(point, k_vved);
	Q_Sort(point, point + k_vved - 1);
	puts("\nПісля сортування");
	outPoint(point, k_vved);
	if (max_group = search_gr(point, &k_vved, &coord_of_max_group))
	{
		printf("\n-----------------------------------------------------------------------\n");
		printf("Координата z = %d повторюється найчастіше. Кількість повторень = %d", coord_of_max_group, max_group + 1);
		printf("\n-----------------------------------------------------------------------\n");
	}
	else
	{
		printf("\n------------------------------------------------------------------\n");
		printf("Немає підгруп точок, що лежать на одній гооризонтальній площині");
		printf("\n------------------------------------------------------------------\n");
	}
	return 0;
}