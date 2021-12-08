#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

struct tovar
{
	int number;
	char* name;
	double price;
	int kol;
};
int n;

int read_int(int* x)
{
	while (scanf("%9d", x) != 1)
	{
		cout << "введены некорректные данные, повторите ввод\n";
		while (fgetc(stdin) != '\n');
		continue;
	}
	if (*x < 0)
	{
		cout << "число не может быть отрицательным, повторите ввод\n";
		read_int(x);
	}
	return *x;
}

double read_double(double* x)
{
	while (scanf("%9lf", x) != 1)
	{
		cout << "введены некорректные данные, повторите ввод\n";
		while (fgetc(stdin) != '\n');
		continue;
	}
	if (*x < 0)
	{
		cout << "число не может быть отрицательным, повторите ввод\n";
		read_double(x);
	}
	return *x;
}

void print_tovar(tovar* fstart, int fn)
{
	double summ = 0;
	printf("%-20s%-20s%-20s%-20s\n", "Название товара", "Цена(руб)", "Количество(кг)", "Общая сумма(руб)");
	printf("--------------------------------------------------------------------------------\n");
	for (int i = 0; i < fn; i++)
	{
		printf("%-20s%-20.2lf%-20d%-20.2lf\n", fstart->name, fstart->price, fstart->kol, fstart->price*fstart->kol);
		summ += fstart->price*fstart->kol;
		fstart++;
	}
	printf("--------------------------------------------------------------------------------\n");
	printf("Всего товаров на сумму\t\t\t\t%20.2lf\n", summ);
	printf("Количество записей в базе  %d\n", fn);
}


bool comp(const tovar& first, const tovar& second)
{
	if (strcmp(first.name, second.name) < 0) return 1;
	else return 0;
}

void nomer_sec(tovar* fstart)
{
	int n_sec, k = 0;
	cout << "введите номер секции\n";
	read_int(&n_sec);
	vector<tovar> B;

	for (int i = 0; i < n; i++)
	{
		if (fstart->number == n_sec)
		{
			B.push_back(*fstart);
			k++;
		}
		fstart++;
	}
	if (k == 0)
		cout << "Нет товаров в этой секции\n";
	else
	{
		cout << "Товары в данной секции:\n";
		tovar* start_B = &B[0];
		sort(B.begin(), B.end(), comp);
		print_tovar(start_B, k);
	}
}

void kol_min(tovar* fstart)
{
	int porog, k = 0;
	cout << "введите количество\n";
	read_int(&porog);
	vector<tovar> C;
	for (int i = 0; i < n; i++)
	{
		if (fstart->kol < porog)
		{
			C.push_back(*fstart);
			k++;
		}
		fstart++;
	}
	if (k == 0)
		cout << "нет товаров с количеством меньше данного\n";
	else
	{
		cout << "товары с количеством меньше данного:\n";
		tovar* start_C = &C[0];
		print_tovar(start_C, k);
	}
}


void new_tovar(tovar* fstart)
{
	cout << "введите название товара\n";
	char name[20];
	cin >> name;
	bool flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(name, fstart->name) == 0)
		{
			fstart->kol++;
			flag = 1;
			break;
		}
		fstart++;
	}
	if (flag == 0)
	{
		int number_new;
		double price_new;
		fstart->name = (char*)malloc(sizeof(char)*strlen(name) + 1);
		strcpy(fstart->name, name);
		fstart->kol = 1;
		cout << "введите цену нового товара\n";
		read_double(&price_new);
		fstart->price = price_new;
		cout << "введите номер секции нового товара\n";
		read_int(&number_new);
		fstart->number = number_new;
		n++;
	}
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	
	char buff[20];
	cout << "введите количество позиций товаров\n";
	read_int(&n);
	tovar* A = new tovar[n];
	tovar* start = A;

	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " товар\nНомер секции\n";
		read_int(&A[i].number);
		cout << "Название товара\n";
		cin >> buff;
		A[i].name = new char[strlen(buff) + 1];
		strcpy(A[i].name, buff);
		cout << "Цена\n";
		read_double(&A[i].price);
		cout << "Количество\n";
		read_int(&A[i].kol);
	}


	int menu;
	while (true)
	{
		cout << "\nДобавить новый элемент\t\t...1\nРаспечатать базу товаров\t...2\nПоиск товаров по номеру секции\t...3\nФильтр по количеству\t\t...4\nВыход из программы\t\t...5\n\n";
		read_int(&menu);
		switch (menu)
		{
		case 1: {new_tovar(start); continue; }
		case 2: {print_tovar(start, n); continue; }
		case 3: {nomer_sec(start); continue; }
		case 4: {kol_min(start); continue; }
		case 5: return 0;
		default: break;
		}
	}
}


