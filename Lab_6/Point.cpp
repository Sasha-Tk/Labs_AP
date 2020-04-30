#pragma once
#include "Point.h"
#include <stdio.h>

int coord_of_max_group;

Point getPoint()
{
	points tmp;
	scanf_s("%d%d%d", &tmp.x, &tmp.y, &tmp.z);
	return tmp;
}

void outPoint(Point* point, int k_vved)
{
	printf("\n------------------------------\n");
	for (int i = 0; i < k_vved; i++)
	{
		printf("Точка №%d (%d, %d, %d)\n\n", (point + i)->num, (point + i)->x, (point + i)->y, (point + i)->z);
	}
}

void swap(Point* a, Point* b) 
{
	Point c;
	c = *a;
	*a = *b;
	*b = c;
}

int search_gr(Point* point, int* k_vved, int* cmg) 
{
	int max_group = 0, p_coord = 0, k_p = 0;
	for (int i = 0; i < *k_vved; i++) {
		if (max_group < k_p) {
			max_group = k_p;
			*cmg = p_coord;
		}
		k_p = 0;
		p_coord = (point + i)->z;
		for (int j = i + 1; j < *k_vved; j++)
			if (p_coord == (point + j)->z)
				k_p++;
	}
	return max_group;

}

void Q_Sort(points* L, points* R) {
	if (L >= R) return;
	points* l = L;
	points* r = R;
	int c = R->x;
	do {
		while (l->x < c) l++;
		while (r->x > c) r--;
		if (l == r) {
			l++;
			r--;
			break;
		}
		if (l < r) {
			swap(l, r);
			l++;
			r--;
		}
	} while (l < r);
	Q_Sort(L, r);
	Q_Sort(l, R);
}

int Entering(Point* point)
{
	int k_vved = 0;
	printf("\nМаксимальна кількість точок - %d\n", N);
	for (int i = 0; i < N; i++) {
		int stoping = 1;
		printf("\nДля введення точки введіть ненульове значення, інакше - 0: ");
		scanf_s("%d", &stoping);
		if (stoping == 0)
			break;
		k_vved++;
		printf("\nВведіть точку з координатами x, y, z\n");
		scanf_s("%d%d%d", &point[i].x, &point[i].y, &point[i].z);
		point[i].num = i + 1;
	}
	return k_vved;
}
