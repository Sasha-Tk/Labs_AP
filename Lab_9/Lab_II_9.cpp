/*Ввести послідовність структур, що мають поля: <Термін> i <Номер сторінки>, та сформувати з них однозв'язний список. Потім відсортувати дані за номерами сторінок - для цього по одному перенести всі елементи в новий список-чергу, перемкнувши відповідні зв'язк. Розробити й застосувати функцію, призначену для доповнення списку новим елементом.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

Item GetItem(void);
void AddNewItem(List** TopPtr,Item newItem);
void AddNewExtraItem(List** TopPtr, Item newExtraItem);
void AddExistingElementToEndOfQueue(List** list,List* element);
void PrintList(List* TopPtr);
void MoveFromListToOtherList(List** list, List** other);
List* SearchMinEl(List* TopPtr);
void DeleteFromList(List** list,List* el);
bool ListIsEmpty(List* TopPtr);
void DeleteList(List* TopPtr);
int CountElements(List* TopPtr);

int main(void)
{
	List* list = NULL;
	List* NewList = NULL;
	system("chcp 1251");
	int stop;
	do
	{
		AddNewItem(&list,GetItem());
		printf("\nДля продовження введіть ненульове значення - інакше 0: ");
		scanf_s("%d", &stop);
	} while (stop);
	printf("\nВведені елементи списку:\n\n");
	PrintList(list);
	printf("\n\n-----------------------\n");
	MoveFromListToOtherList(&list,&NewList);
	printf("\nПосортовані елементи списку:\n");
	PrintList(NewList);
	printf("\n\n-----------------------\n");
	printf("\nЩоб ввести додатковий елемент - введіть ненульове значення: ");
	scanf_s("%d", &stop);
	while (stop)
	{
		AddNewExtraItem(&NewList, GetItem());
		printf("\n\nДля продовження введіть ненульове значення - інакше 0: ");
		scanf_s("%d", &stop);
	}
	printf("\nДоповнений список:\n");
	PrintList(NewList);
	DeleteList(list);
	DeleteList(NewList);
	return 0;
}

Item GetItem(void)
{
	Item tmp;
	char* buffer = (char*)malloc(sizeof(char) * 255);
	printf("\nВведіть номер сторінки: ");
	scanf("%d", &tmp.pageNumber);
	if (tmp.pageNumber <= 0)
	{
		exit(-1);
	}
	rewind(stdin);
	printf("\nВведіть визначення: ");
	gets_s(buffer, 255);
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

void AddNewExtraItem(List** TopPtr, Item newExtraItem)
{
	List* new_el = (List*)malloc(sizeof(List));
	new_el->item = newExtraItem;
	new_el->next = NULL;
	List* ptr = *TopPtr;
	List* prev = *TopPtr;
	if (*TopPtr == NULL)
	{
		return;
	}
	while (ptr != NULL && newExtraItem.pageNumber >= ptr->item.pageNumber)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == *TopPtr&&ptr!=NULL)
	{
		new_el->next = ptr->next;
		*TopPtr = new_el;
	}
	else if (ptr == NULL&&prev!=NULL)
	{
		prev->next = new_el;
		new_el->next = NULL;
	}
	else
	{
		prev->next = new_el;
		new_el->next = ptr;
	}
}

void AddExistingElementToEndOfQueue(List** list, List* element)
{
	List* ptr = *list;
	if (*list == NULL)
	{
		*list = element;
		return;
	}
	while (ptr->next!= NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = element;
}

void PrintList(List* TopPtr)
{
	List* ptr = TopPtr;
	while (ptr != NULL)
	{
		printf("\n\tст.%-4d    %s", ptr->item.pageNumber, ptr->item.definition);
		ptr = ptr->next;
	}
}

void MoveFromListToOtherList(List** list, List** other)
{
	List* newEl;
	while (!ListIsEmpty(*list))
	{
		newEl = SearchMinEl(*list);
		DeleteFromList(list,newEl); 
		AddExistingElementToEndOfQueue(other, newEl);
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