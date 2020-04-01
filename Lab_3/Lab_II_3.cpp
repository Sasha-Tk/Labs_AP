#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

struct points {
	int x;
	int y;
	int z;
	int num;
};
points getPoint();
void swap(points*, points*);
void Q_Sort(points*, points*);
void outPoint(points*, int);
int search_gr(points*, int, int*);

int main(void) {
	struct points point[N];
	int max_group = 0, k_vved = 0;
	int coord_of_max_group;
	system("chcp 1251");
	printf("\nМаксимальна кількість точок - %d\n",N);
	for (int i = 0; i < N; i++) {
		int stoping = 1;
		printf("\nДля введення точки введіть ненульове значення, інакше - 0: ");
		scanf_s("%d", &stoping);
		if (stoping == 0)
			break;
		k_vved++;
		printf("\nВведіть точку з координатами x, y, z\n");
		point[i] = getPoint();
		point[i].num = i + 1;
	}
	if (k_vved == 0) {
		printf("\nВи не ввели жодної точки!\n");
		return 0;
	}
	puts("\nДо сортування");
	outPoint(point, k_vved);
	Q_Sort(point, point + k_vved - 1);
	puts("\nПісля сортування");
	outPoint(point, k_vved);
	if (max_group = search_gr(point, k_vved, &coord_of_max_group))
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

int search_gr(points* point, int k_vved, int* cmg) {
	int max_group = 0, p_coord = 0, k_p = 0;
	for (int i = 0; i < k_vved; i++) {
		if (max_group < k_p) {
			max_group = k_p;
			*cmg = p_coord;
		}
		k_p = 0;
		p_coord = (point+i)->z;
		for (int j = i + 1; j < k_vved; j++)
			if (p_coord == (point + j)->z)
				k_p++;
	}
	return max_group;
}

points getPoint()
{
	points tmp;
	scanf_s("%d%d%d", &tmp.x, &tmp.y, &tmp.z);
	return tmp;
}

void outPoint(points* Point, int k_vved)
{
	printf("\n------------------------------\n");
	for (int i = 0; i < k_vved; i++)
	{
		printf("Точка №%d (%d, %d, %d)\n\n", (Point+i)->num, (Point + i)->x, (Point + i)->y, (Point + i)->z);
	}
}

void swap(points* a, points* b) {
	points c;
	c = *a;
	*a = *b;
	*b = c;
}