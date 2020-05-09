/*Ввести послідовність структур, що мають поля: <Термін>
 i <Номер сторінки>, та сформувати з них однозв'язний 
список. Потім відсортувати дані за номерами сторінок - для
 цього по одному перенести всі елементи в новий список-чергу,
 перемкнувши відповідні зв'язк. Розробити й застосувати 
функцію, призначену для доповнення списку новим елементом.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 30
typedef struct item
{
	int pageNumber;
	char* definition;
}Item;

typedef struct list
{
	Item item;
	struct list* next;
}List;

Item GetItem(FILE** file);
void AddNewItem(List** TopPtr, Item newItem);
void AddExistingItemToEndOfQueue(List** list, List* item);
void PrintList(List* TopPtr, FILE* flow);
void MoveFromListToOtherList(List** list, List** other);
List* SearchMinEl(List* TopPtr);
void DeleteFromList(List** list, List* el);
bool ListIsEmpty(List* TopPtr);
void DeleteList(List* TopPtr);
int CountElements(List* TopPtr);
bool OpenFile(FILE** pointer, const char* f_name, const char* mode);

int main(void)
{	
	system("chcp 1251");
	List* list = NULL;
	List* NewList = NULL;
	FILE* file, * file_w;
	char* f_name, * fw_name;
	f_name = (char*)malloc(N * sizeof(char));
	fw_name = (char*)malloc(N * sizeof(char));
	printf("\nВведіть ім'я файлу з даними: ");
	gets_s(f_name, N);
	printf("\nВведіть ім'я файлу, в який записувати дані: ");
	gets_s(fw_name, N);
	if (!OpenFile(&file, f_name, "r")||!OpenFile(&file_w, fw_name, "w"))
	{
		exit(1);
	}
	while (!feof(file))
	{
		AddNewItem(&list, GetItem(&file));
	}
	printf("\nВведені елементи списку:\n\n");
	PrintList(list, stdout);
	printf("\n\n-----------------------\n");
	MoveFromListToOtherList(&list, &NewList);
	printf("\nПосортовані елементи списку:\n");
	PrintList(NewList, stdout);
	PrintList(NewList, file_w);
	DeleteList(list);
	DeleteList(NewList);
	return 0;
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

Item GetItem(FILE** file)
{
	Item tmp;
	char* buffer = (char*)malloc(sizeof(char) * 255);
	fscanf(*file,"%d", &tmp.pageNumber);
	if (tmp.pageNumber <= 0)
	{
		exit(-1);
	}
	fgets(buffer, 255, *file);
	if (strlen(buffer) == 0)
	{
		exit(-2);
	}
	tmp.definition = buffer;
	return tmp;
}

void AddNewItem(List** TopPtr, Item item)
{
	List* new_el = (List*)malloc(sizeof(List));
	static List* last;
	new_el->item = item;
	new_el->next = NULL;
	if (*TopPtr == NULL)
	{
		*TopPtr = new_el;
		last = new_el;
	}
	else
	{
		last->next = new_el;
		last = new_el;
		new_el->item = item;
	}
}

void AddExistingItemToEndOfQueue(List** list, List* item)
{
	List* ptr = *list;
	if (*list == NULL)
	{
		*list = item;
		return;
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = item;
}

void PrintList(List* TopPtr, FILE* flow)
{
	List* ptr = TopPtr;
	while (ptr != NULL)
	{
		fprintf(flow,"\n\tст.%-4d    %s", ptr->item.pageNumber, ptr->item.definition);
		ptr = ptr->next;
	}
}

void MoveFromListToOtherList(List** list, List** other)
{
	List* newEl;
	while (!ListIsEmpty(*list))
	{
		newEl = SearchMinEl(*list);
		DeleteFromList(list, newEl);
		AddExistingItemToEndOfQueue(other, newEl);
	}
}

List* SearchMinEl(List* TopPtr)
{
	List* min_el = TopPtr;
	List* el = min_el;
	while (el != NULL)
	{
		if (el->item.pageNumber < min_el->item.pageNumber)
		{
			min_el = el;
		}
		el = el->next;
	}
	return min_el;
}

void DeleteFromList(List** TopPtr, List* el)
{
	if (el == *TopPtr)
	{
		*TopPtr = el->next;
		el->next = NULL;
	}
	else
	{
		List* prev = *TopPtr;
		while (prev->next != el)
		{
			prev = prev->next;
		}
		prev->next = el->next;
		el->next = NULL;
	}
}

bool ListIsEmpty(List* TopPtr)
{
	if (TopPtr == NULL)
	{
		return true;
	}
	return false;
}

void DeleteList(List* TopPtr)
{
	List* ptr = TopPtr;
	List* next;
	int i = CountElements(TopPtr);
	while (i)
	{
		next = ptr->next;
		free(ptr->item.definition);
		free(ptr);
		ptr = next;
		i--;
	}
}

int CountElements(List* TopPtr)
{
	int i = 0;
	List* ptr = TopPtr;
	while (ptr != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return i;
}