#include <iostream>
#include <iomanip>
#include <windows.h>
#include <chrono>

using namespace std;

long int expt(long int x, long int n) //Only integer and n >= 0.
{
	if (n == 0)
	{
		return 1;
	}
	long int answer = 1;
	while (n != 0)
	{
		answer *= x;
		n -= 1;
	}
	return answer;
}

void array_filling(short int** arr, short int n, short int m)
{
	srand(time(NULL));
	for (short int i = 0; i < n; i++)
	{
		for (short int j = 0; j < m; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
	cout << "The matrix is successfully filled.\n";
}

void array_filling_manual(short int** arr, short int n, short int m)
{
	cout << "Enter arabic natural numbers less than 100, by separating the elements with the help of button 'Enter'.\n";
	for (short int i = 0; i < n; i++)
	{
		for (short int j = 0; j < m; j++)
		{
			cout << "arr[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> arr[i][j];
		}
	}
	cout << "The matrix is successfully filled.\n";
}

void array_print(short int** arr, short int n, short int m)
{
	for (short int i = 0; i < n; i++)
	{
		for (short int j = 0; j < m; j++)
		{
			cout << setfill(' ') << setw(2) << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << "The array is successfully printed.\n";
}

void array_print_WA(short int** arr, short int n, short int m)
{
	cout << "det({";
	for (short int i = 0; i < n; i++)
	{
		cout << "{";
		for (short int j = 0; j < m; j++)
		{
			cout << arr[i][j];
			if (j != m - 1)
			{
				cout << ",";
			}
		}
		cout << "}";
		if (i != n - 1)
		{
			cout << ",";
		}
	}
	cout << "})\n";
}

void matr_saddle_points(short int** arr, short int n, short int m)
{
	short int max = -1;
	short int min = 100;
	short int counter = 0;
	for (short int i = 0; i < n; i++)
	{
		//Поиск минимума и максимума в строке
		for (short int j = 0; j < m; j++)
		{
			if (arr[i][j] > max)
			{
				max = arr[i][j];
			}
			if (arr[i][j] < min)
			{
				min = arr[i][j];
			}
		}
		//Седловые точки при минимуме и максимуме в строке.
		for (short int j = 0; j < m; j++)
		{
			if (arr[i][j] == min)
			{
				for (short int p = 0; p < n; p++)
				{
					if (arr[p][j] > arr[i][j])
					{
						break;
					}
					if (p == n - 1)
					{
						cout << i << " " << j << endl;
						counter += 1;
					}
				}
			}
			if (arr[i][j] == max)
			{
				for (short int p = 0; p < n; p++)
				{
					if (arr[p][j] < arr[i][j])
					{
						break;
					}
					if (p == n - 1)
					{
						cout << i << " " << j << endl;
						counter += 1;
					}
				}
			}
		}
		min = 100;
		max = -1;
	}
	if (counter == 0)
	{
		cout << "No one was found.\n";
	}
}

long int matr_determinant(short int** arr, short int n, short int m);

long int matr_minor(short int** arr, short int n, short int m, short int r, short int c)
{
	short int* n2;
	short int* m2;
	n2 = new short int(n - 1);
	m2 = new short int(m - 1);
	short int* i2;
	short int* j2;
	i2 = new short int(0);
	j2 = new short int(0);
	short int** arr2;
	arr2 = new short int* [*n2];
	for (short int z = 0; z < *n2; z++)
	{
		arr2[z] = new short int[*m2];
	}
	for (short int i = 0; i < *n2; i++)
	{
		if (i == r)
		{
			*i2 = 1;
		}
		for (short int j = 0; j < *m2; j++)
		{
			if (j == c)
			{
				*j2 = 1;
			}
			arr2[i][j] = arr[i + *i2][j + *j2];
		}
		*j2 = 0;
	}
	*i2 = 0;
	//array_print(arr2, *n2, *m2);
	long int temp = matr_determinant(arr2, *n2, *m2);
	delete j2;
	delete i2;
	for (short int z = 0; z < *n2; z++)
	{
		delete[] arr2[z];
	}
	delete[] arr2;
	delete n2;
	delete m2;
	return temp;
}

long int matr_determinant(short int** arr, short int n, short int m)
{
	long int determinant = 0;
	if (n == 1)
	{
		determinant = arr[0][0];
	}
	else if (n == 2)
	{
		determinant = (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
	}
	else if (n == 3)
	{
		determinant = ((arr[0][0] * arr[1][1] * arr[2][2]) + (arr[0][1] * arr[1][2] * arr[2][0]) + (arr[0][2] * arr[1][0] * arr[2][1]))
			- ((arr[0][2] * arr[1][1] * arr[2][0]) + (arr[0][0] * arr[1][2] * arr[2][1]) + (arr[0][1] * arr[1][0] * arr[2][2]));
	}
	else for (short int j = 0; j < m; j++)
	{
		determinant += expt(-1, (1 + (j + 1))) * arr[0][j] * matr_minor(arr, n, m, 0, j);
	}
	return determinant;
}

int main()
{
	char end = 'y';
	while (end == 'y')
	{
		// N, M - размерность массива - строки и столбцы соответственно.
		short int* n,* m;
		n = new short int;
		m = new short int;
		cout << "Enter the number of rows in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < only integer number <= 32767\n";
		cin >> *n;
		cout << "Enter the number of columns in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < only integer number <= 32767\n";
		cin >> *m;
		// Определение максимального количества элементов.
		long int* amount_of_elements;
		amount_of_elements = new long int(*n * *m);
		MEMORYSTATUSEX ms;
		ms.dwLength = sizeof(ms);
		GlobalMemoryStatusEx(&ms);
		cout << (ms.ullTotalPhys / 1024 / 1024) << " Mbyte - total.\n";
		cout << (ms.ullAvailPhys / 1024 / 1024) << " Mbyte - available.\n";
		if (*amount_of_elements > ((ms.ullAvailPhys - (256 * 1024 * 1024)) / 2)) //256 Мб в запасе.
		{
			cout << "Matrix of the specified size cannot be created - not enough RAM.\n";
			cout << "Please, enter a smaller matrix size...\n";
		}
		else
		{
			cout << "The matrix has been successfully created.\n";
			cout << "Please, wait...\n";
			//Определение динамического массива.
			short int** arr;
			arr = new short int* [*n];
			for (short int i = 0; i < *n; i++)
			{
				arr[i] = new short int[*m];
			}
			cout << "Press 1 or 2 and Enter:\n";
			cout << "1. array_filling\n";
			cout << "2. array_filling_manual\n";
			short int* inp = new short int;
			cin >> *inp;
			if (*inp == 1)
			{
				array_filling(arr, *n, *m);
			}
			else
			{
				array_filling_manual(arr, *n, *m);
			}
			delete inp;
			//Обновление данных по оп. памяти.
			GlobalMemoryStatusEx(&ms);
			cout << (ms.ullAvailPhys / 1024 / 1024) << " Mbyte - after allocating memory for the array.\n";
			if (*n > 70 or *m > 70)
			{
				cout << "Due to the large size of the matrix, the output formatting will be broken or may take too long, do you want to print the matrix exactly?\n";
				cout << "enter 'y'(for yes) or 'n'(for no)...\n";
				char* ans;
				ans = new char;
				cin >> *ans;
				if (*ans == 'y')
				{
					array_print(arr, *n, *m);
				}
				delete ans;
			}
			else
			{
				array_print(arr, *n, *m);
			}
			cout << "Saddle points index:\n";
			matr_saddle_points(arr, *n, *m);
			if (*n == *m)
			{
				if (*n <= 10)
				{
					cout << "Please, wait...\n";
					cout << "Determinant = " << matr_determinant(arr, *n, *m) << endl;
					array_print_WA(arr, *n, *m);
				}
				else
				{
					cout << "The determinants of such high orders of magnitude are counted slowly, do you want to start the calculations exactly?\n";
					cout << "enter 'y'(for yes) or 'n'(for no)...\n";
					char* ans2;
					ans2 = new char;
					cin >> *ans2;
					if (*ans2 == 'y')
					{
						cout << "Please, wait...\n";
						cout << "Determinant = " << matr_determinant(arr, *n, *m) << endl;
						array_print_WA(arr, *n, *m);
					}
					delete ans2;
				}
			}
			else
			{
				cout << "Error, only square matrices!\n";
			}
			//Удаление динамического массива.
			for (short int i = 0; i < *n; i++)
			{
				delete[] arr[i];
			}
			delete[] arr;
		}
		delete n;
		delete m;
		delete amount_of_elements;
		//Проверка на повторный запуск программы.
		cout << "Run this program again now? (y/n) (one lowercase letter and 'Enter')\n";
		cin >> end;
	}
	return 0;
}