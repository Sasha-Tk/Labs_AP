#pragma once

#define N 100
typedef struct points {
	int x;
	int y;
	int z;
	int num;
}Point;

int Entering(Point* point);
Point getPoint();
void swap(Point*, Point*);
void Q_Sort(Point*, Point*);
void outPoint(Point*, int);
int search_gr(Point*, int*, int*);
