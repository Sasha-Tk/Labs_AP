#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define S 162
#define N 4

typedef struct Date
{
	char dates[S] = { 0 };
	int k = 0;
	int n = 0;
} Date;

int DataEntry(Date* D);
void SetStruct(Date* D);
int CountDates(char* dates);
bool NoDate(Date* dates, int n);
Date SearchMaxData_V3(char* c_date, int n, Date* D, ...);
char* SearchMaxStrDate(char* c_date, char* dates, int k_dates);
void GetDate(char* str_date, int* date);
void DiffDates(char* DATE, char* C_DATE, int* d_date);
void StrCopyDate(char* d_1, char* d_2);
void CopyDate(int* d_1, int* d_2);
bool DateIsLess(int* less, int* bigger);

int main(void) {
	system("chcp 1251");
	Date dates[N], max;
	char c_date[11], * max_d;
	int d_date[3];
	if (DataEntry(dates) == 0)
	{
		return 0;
	}
	printf("\nВведіть сьогоднішню дату у форматі дд.мм.рр ");
	gets_s(c_date);
	max = SearchMaxData_V3(c_date, N, dates, (dates + 1), (dates + 2), (dates + 3));
	max_d = SearchMaxStrDate(c_date, max.dates, max.k);
	printf("\n\nЗнайдено структуру №%d з найближчою до сьогоднішньої датою: %s", max.n, max_d);
	DiffDates(max_d, c_date, d_date);
	printf("\nРізниця дат - %d р, %d м, %d д", d_date[0], d_date[1], d_date[2]);
	return 0;
}

int DataEntry(Date* dates)
{
	printf("Дати (не більше %d для кожної структури) "
		"потрібно вводити у форматі дд.мм.рр через кому!\n", (S - S / 10 * 2) / 10);
	printf("Структур доступно - %d\n", N);
	for (int i = 0; i < N; i++)
	{
		printf("\nВведіть дати у структуру №%d: ", i + 1);
		SetStruct(dates + i);
		(dates + i)->n = i + 1;
		printf("\nУспішно введено %d дат у структуру №%d/%d\n", (dates + i)->k, (dates + i)->n, N);
	}
	if (NoDate(dates, N) == true)
	{
		printf("\nВи не ввели жодної адреси в кожну із структур!");
		return 0;
	}
	return !0;
}

void SetStruct(Date* D)
{
	gets_s(D->dates);
	D->k = CountDates(D->dates);
	if (D->k == 0)
		printf("Ви не ввели жодної дати!");
}

int CountDates(char* dates)
{
	char* p = dates;
	int i = 0;
	if (*p == '\0')
		return 0;
	while (*p != '\0')
	{
		if (*p == ',' && *(p + 1) == ' ' || *p == ' ' && *(p - 1) != ',')
			i++;
		p++;
	}
	return i + 1;
}

bool NoDate(Date* dates, int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((dates + i)->k != 0)
			return false;
	}
	return true;
}

Date SearchMaxData_V3(char* c_date, int n, Date* D, ...) {
	va_list ptr;
	va_start(ptr, D);
	Date max_s, s;
	int date[3];
	int m_date[3];
	char* max_in_str;
	max_s = *D;
	max_in_str = SearchMaxStrDate(c_date, D->dates, D->k);
	DiffDates(max_in_str, c_date, m_date);
	for (int i = 1; i < n; i++)
	{
		s = *(va_arg(ptr, Date*));
		max_in_str = SearchMaxStrDate(c_date, s.dates, s.k);
		DiffDates(max_in_str, c_date, date);
		if (DateIsLess(date, m_date))
		{
			max_s = s;
			CopyDate(m_date, date);
		}
	}
	va_end(ptr);
	return max_s;
}

char* SearchMaxStrDate(char* c_date, char* dates, int k_dates)
{
	static char max_date[11];
	char* d_ptr = dates;
	int diff_d[3];
	int min_diff_d[3];
	if (k_dates == 1) return dates;
	DiffDates(d_ptr, c_date, min_diff_d);
	StrCopyDate(max_date, d_ptr);
	while (*d_ptr >= '0' && *d_ptr <= '9' || *d_ptr == '.') d_ptr++;
	for (int i = 1; i < k_dates; i++)
	{
		while (*d_ptr < '0' || *d_ptr > '9') d_ptr++;
		DiffDates(d_ptr, c_date, diff_d);
		if (DateIsLess(diff_d, min_diff_d))
		{
			CopyDate(min_diff_d, diff_d);
			StrCopyDate(max_date, d_ptr);
		}
		while (*d_ptr >= '0' && *d_ptr <= '9' || *d_ptr == '.') d_ptr++;
	}
	return max_date;
}

void GetDate(char* str_date, int* date)
{
	char* p = str_date;
	date[2] = atoi(p);
	while (*p != '.') p++;
	date[1] = atoi(++p);
	while (*p != '.') p++;
	date[0] = atoi(++p);
}

void DiffDates(char* DATE, char* C_DATE, int* d_date)
{
	int date[3], c_date[3];
	GetDate(DATE, date);
	GetDate(C_DATE, c_date);
	if (c_date[0] == date[0])
	{
		d_date[0] = 0;
		if (c_date[1] == date[1])
		{
			d_date[1] = 0;
			if (c_date[2] == date[2]) {
				d_date[2] = 0;
				return;
			}
			if (c_date[2] > date[2])
				d_date[2] = c_date[2] - date[2];
			if (c_date[2] < date[2])
				d_date[2] = date[2] - c_date[2];
			return;
		}
		if (c_date[1] > date[1]) {
			d_date[1] = c_date[1] - date[1];
			d_date[2] = c_date[2] - date[2];
		}
		if (date[1] > c_date[1]) {
			d_date[1] = date[1] - c_date[1];
			d_date[2] = date[2] - c_date[2];
		}

		if (d_date[2] < 0)
		{
			d_date[2] += 30;
			d_date[1]--;
		}
	}
	if (c_date[0] > date[0])
	{
		d_date[0] = c_date[0] - date[0];
		d_date[1] = c_date[1] - date[1];
		if (d_date[1] < 0)
		{
			d_date[1] = 12 + d_date[1];
			d_date[0]--;
		}
		d_date[2] = c_date[2] - date[2];
		if (date[1] == c_date[1])
		{
			d_date[1] = 0;
			if (c_date[2] > date[2])
				d_date[2] = c_date[2] - date[2];
			if (c_date[2] < date[2])
				d_date[2] = date[2] - c_date[2];
		}
		if (d_date[2] < 0)
		{
			d_date[2] = 30 + d_date[2];
			d_date[1]--;
		}
	}
	if (date[0] > c_date[0])
	{
		d_date[0] = date[0] - c_date[0];
		d_date[1] = date[1] - c_date[1];
		if (d_date[1] < 0)
		{
			d_date[1] = 12 + d_date[1];
			d_date[0]--;
		}
		d_date[2] = date[2] - c_date[2];
		if (date[1] == c_date[1])
		{
			d_date[1] = 0;
			if (c_date[2] > date[2])
				d_date[2] = c_date[2] - date[2];
			if (c_date[2] < date[2])
				d_date[2] = date[2] - c_date[2];
		}
		if (d_date[2] < 0)
		{
			d_date[2] = 30 + d_date[2];
			d_date[1]--;
		}
	}
}

void StrCopyDate(char* d_1, char* d_2)
{
	while (*d_2 >= '0' && *d_2 <= '9' || *d_2 == '.' && *d_2 != '\0')
	{
		*d_1++ = *d_2++;
	}
	*d_1 = '\0';
}

void CopyDate(int* d_1, int* d_2)
{
	for (int i = 0; i < 3; i++)
	{
		*(d_1 + i) = *(d_2 + i);
	}
}

bool DateIsLess(int* less, int* bigger)
{
	if ((less[0] < bigger[0]) || (less[0] == bigger[0] && less[1] < bigger[1]) || (less[0] == bigger[0] && less[1] == bigger[1] && less[2] < bigger[2]))
	{
		return true;
	}
	else return false;
}