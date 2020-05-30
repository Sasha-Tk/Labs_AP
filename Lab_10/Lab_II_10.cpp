#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define M 56

typedef struct info_in_tree
{
	char* bd_code;
	int decimal_value;
}Info;


typedef struct tree_node
{
	Info info;
	tree_node* left;
	tree_node* right;
}Node;


void ReadNameOfFile(char** f_name);
bool OpenFile(FILE** pointer, const char* f_name, const char* mode);
Info ReadNode(FILE** pointer);
int ToDecimal(char* bd_number);
void IsCorrect(const char* bd_digit);
bool IsMinusSign(const char* bd_digit);
void AddEementToTree(Node** root, Info new_el);
void PrintTree(Node* root);
int HeightOfTree(Node* root);
Node* SearchNode(Node* root, int value);
void Searching(Node* root);
void SearchNodesAtRequstLevel(Node* root);
void PrintNodesAtRequestLevel(Node* root, int level);
void DeleteTree(Node* root);

int main(void)
{
	system("chcp 1251");
	FILE* file;
	Node* root = NULL;
	char* f_name;
	ReadNameOfFile(&f_name);
	OpenFile(&file, f_name, "r");
	while (!feof(file))
	{
		AddEementToTree(&root, ReadNode(&file));
	}
	PrintTree(root);
	Searching(root);
	SearchNodesAtRequstLevel(root);
	DeleteTree(root);
	root = NULL;
	_fcloseall();
	return 0;
}

void ReadNameOfFile(char** f_name)
{
	*f_name = (char*)malloc(N * sizeof(char));
	printf("\nВведіть ім'я файлу з даними: ");
	gets_s(*f_name, N);
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

Info ReadNode(FILE** pointer)
{
	Info tmp;
	char* buffer = (char*)malloc(M);
	char buffer_copy[M];
	int len;
	fgets(buffer, M, *pointer);
	len = strlen(buffer);
	if (len < 4)
	{
		printf("\nНевірно вказане двійково-десяткове число: %s!", buffer);
	}
	if (buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}
	strcpy_s(buffer_copy, M, buffer);
	tmp.bd_code = buffer;
	tmp.decimal_value = ToDecimal(buffer_copy);
	return tmp;
}

int ToDecimal(char* bd_number)
{
	int dec_value = 0, digit;
	char* tmp, * end;
	bool is_negative;
	tmp = strtok(bd_number, " \0");
	is_negative = IsMinusSign(tmp);
	if (!is_negative)
	{
		dec_value = strtol(tmp, &end, 2);
	}
	tmp = strtok(NULL, " ");
	if (tmp != NULL && is_negative == false && dec_value == 0)
	{
		printf("\nНекоректне значення першої двійково-десяткової цифри: %s!", tmp);
		exit(-3);
	}
	while (tmp != NULL)
	{
		IsCorrect(tmp);
		digit = strtol(tmp, &end, 2);
		dec_value = digit + dec_value * 10;
		tmp = strtok(NULL, " ");
	}
	if (is_negative == true)
	{
		dec_value *= -1;
	}
	return dec_value;
}

void IsCorrect(const char* bd_digit)
{
	int dec_value = 0;
	char* end;
	if (strlen(bd_digit) != 4)
	{
		printf("\nНевірно вказана двійково-десяткова цифра: %s!", bd_digit);
		exit(-1);
	}
	dec_value = strtol(bd_digit, &end, 2);
	if (dec_value > 9)
	{
		printf("\nНекоректне значення двійково-десяткової цифри: %s!", bd_digit);
		exit(-2);
	}
}

bool IsMinusSign(const char* bd_digit)
{
	int dec_value = 0;
	char* end;
	dec_value = strtol(bd_digit, &end, 2);
	if (dec_value == 13)
	{
		return true;
	}
	else if (dec_value < 10 && dec_value >= 0)
	{
		return false;
	}
	else
	{
		printf("\nНекоректне значення першої двійково-десяткової цифри: %s!", bd_digit);
		exit(-3);
	}
}

void AddEementToTree(Node** root, Info new_el)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->info = new_el;
	if (NULL == *root)
	{
		new_node->left = NULL;
		new_node->right = NULL;
		*root = new_node;
		return;
	}
	if (new_node->info.decimal_value > (*root)->info.decimal_value)
	{
		AddEementToTree(&((*root)->right), new_node->info);
	}
	if (new_node->info.decimal_value < (*root)->info.decimal_value)
	{
		AddEementToTree(&((*root)->left), new_node->info);
	}
}

void PrintTree(Node* root)
{
	if (NULL == root)
	{
		return;
	}
	PrintTree(root->right);
	PrintTree(root->left);
	printf("\n\t%s = %d", root->info.bd_code, root->info.decimal_value);
}

Node* SearchNode(Node* root, int value)
{
	Node* node_ptr = root;
	while (true)
	{
		if (NULL == node_ptr)
		{
			return NULL;
		}
		if (node_ptr->info.decimal_value == value)
		{
			return node_ptr;
		}
		else if (value > node_ptr->info.decimal_value)
		{
			node_ptr = node_ptr->right;
		}
		else
		{
			node_ptr = node_ptr->left;
		}
	}
}

void Searching(Node* root)
{
	int stop = 1, number;
	Node* finded_node;
	while (stop)
	{
		printf("\nВведіть число для пошуку вузла в дереві: ");
		scanf_s("%d", &number);
		finded_node = SearchNode(root, number);
		if (NULL == finded_node)
		{
			printf("\nВказаного числа %d не знайдено в дереві!\n", number);
		}
		else
		{
			printf("\nВказане число %d знайдено у дереві, його 2-10 код: %s", number, finded_node->info.bd_code);
		}
		printf("\nЩоб продовжити пошук, введіть 1, інакше - 0: ");
		scanf_s("%d", &stop);
	}
}

void SearchNodesAtRequstLevel(Node* root)
{
	int stop = 1;
	int level;
	while (stop)
	{
		printf("\n\nВведіть рівень дерева для видруку: ");
		scanf_s("%d", &level);
		if (level<0 || level>HeightOfTree(root))
		{
			printf("Такого рівня в дереві немає!");
			exit(-4);
		}
		else
		{
			PrintNodesAtRequestLevel(root, level);
		}
		printf("\nЩоб продовжити пошук, введіть 1, інакше - 0: ");
		scanf_s("%d", &stop);
	}
}

void PrintNodesAtRequestLevel(Node* root, int level)
{
	if (NULL == root)
	{
		return;
	}
	if (0 == level)
	{
		printf("%s = %d\t", root->info.bd_code, root->info.decimal_value);
		return;
	}
	else
	{
		PrintNodesAtRequestLevel(root->left, level - 1);
		PrintNodesAtRequestLevel(root->right, level - 1);
	}
}

void DeleteTree(Node* root)
{	
	if (NULL == root)
	{
		return;
	}
	Node* r_root = root->right, *l_root = root->left;
	DeleteTree(l_root);
	free(root->info.bd_code);
	free(root);
	DeleteTree(r_root);
	root = NULL;
}


int HeightOfTree(Node* root)
{
	int left_tree_height;
	int right_tree_height;
	if (NULL == root)
	{
		return 0;
	}
	left_tree_height = HeightOfTree(root->left);
	right_tree_height = HeightOfTree(root->right);
	return right_tree_height > left_tree_height ? right_tree_height + 1 : left_tree_height + 1;
}