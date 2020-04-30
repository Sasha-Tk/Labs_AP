/*Розробити функцію, яка вилуча з речення всі слова, 
що містять задану комбнацію символів. Використовуючи 
розроблену функцію, створити новий текстовий файл на 
основі заданого, вилучивги з нього всі слова, що 
'містять вказане буквосполучення*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000
#define M 10
#define S 30

bool OpenFile(FILE** pointer, const char* f_name, const char* mode);
char* DeleteWords(char*, const char*);
char* FindBeginingOfWord(char* str);
char* FindEndOfWord(char* word);

int main(void)
{
	system("chcp 1251");
	FILE* file = nullptr , * new_file=nullptr;
	char buffer[N], c_smb[M], file_name[S], new_file_name[S];
	printf("\nВведіть ім'я файлу з текстом: ");
	gets_s(file_name);
	if (!OpenFile(&file, file_name, "r"))
	{
		return 0;
	}
	printf("\nВведіть комбінацію символів: ");
	gets_s(c_smb);
	printf("\nВведіть ім'я нового файлу: ");
	gets_s(new_file_name);
	if(!OpenFile(&new_file, new_file_name, "w"))
	{
		return 0;
	}
	while (fgets(buffer, N, file) != NULL)
	{
		printf("\n\n***Речення до заміни***\n\n");
		puts(buffer);
		printf("\n\n***Речення після заміни***\n\n");
		puts(DeleteWords(buffer, c_smb));
		fputs(DeleteWords(buffer, c_smb), new_file);
	}
	_fcloseall();
	return 0;
}

char* DeleteWords(char* sentence, const char* smbCombination)
{
	static char new_sentence[N];
	char* begining, * end, * foundComb;
	char* p = sentence, * new_p = new_sentence;
	begining = FindBeginingOfWord(sentence);
	end = FindEndOfWord(begining);
	while (begining != NULL)
	{
		foundComb = strstr(begining, smbCombination);
		if (begining <= foundComb && foundComb <= end)
		{
			p = end;
		}
		begining = FindBeginingOfWord(end);
		if (begining == NULL)
		{
			while (*p != '\0')
			{
				*new_p++ = *p++;
			}
			break;
		}
		while (p < begining)
		{
			*new_p++ = *p++;
		}
		end = FindEndOfWord(begining);
	}
	++* new_p = '\0';
	return new_sentence;
}

char* FindBeginingOfWord(char* str)
{
	char* p = str;
	while (*p == ' ' || *p == ',' || *p == '.' || *p == '!' || *p == ':' || *p == '(' || *p == ')' || *p == '\0')
	{
		if (*p == '\0')
		{
			return NULL;
		}
		p++;
	}
	return p;
}

char* FindEndOfWord(char* word)
{
	char* p = word;
	while (*p != ' ' && *p != ',' && *p != '!' && *p != '(' && *p != ')' && *p != ':' && *p != '\0')
		p++;
	return p;
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