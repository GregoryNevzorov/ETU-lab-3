#include <iostream>
#include <windows.h>
#include <chrono>

using namespace std;

void array_filling(short int** arr, short int n, short int m)
{
	srand(time(NULL));
	for (short int i = 0; i < n; i++)
	{
		for (short int j = 0; j < m; j++)
		{
			arr[i][j] = rand() % 10;
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
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << "The array is successfully printed.\n";
}


int main()
{
	char end = 'y';
	while (end == 'y')
	{
		// N, M - размерность массива - строки и столбцы соответственно.
		short int n, m;
		cout << "Enter the number of rows in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < only integer number <= 32767\n";
		cin >> n;
		cout << "Enter the number of columns in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < only integer number <= 32767\n";
		cin >> m;
		// Определение максимального количества элементов.
		long int amount_of_elements = n * m;
		MEMORYSTATUSEX ms;
		ms.dwLength = sizeof(ms);
		GlobalMemoryStatusEx(&ms);
		cout << (ms.ullTotalPhys / 1024 / 1024) << " Mbyte - total.\n";
		cout << (ms.ullAvailPhys / 1024 / 1024) << " Mbyte - available.\n";
		if (((amount_of_elements * 2)/* + (amount_of_elements / 8)*/) > (ms.ullAvailPhys - (256 * 1024 * 1024))) //256 Мб в запасе.
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
			arr = new short int* [n];
			for (short int i = 0; i < n; i++)
			{
				arr[i] = new short int[m];
			}
			array_filling(arr, n, m);
			//Обновление данных по оп. памяти.
			GlobalMemoryStatusEx(&ms);
			cout << (ms.ullAvailPhys / 1024 / 1024) << " Mbyte - after allocating memory for the array.\n";
			if (n > 100 or m > 100)
			{
				cout << "Due to the large size of the matrix, the output formatting will be broken or may take too long, do you want to print the matrix exactly?\n";
				cout << "enter 'y'(for yes) or 'n'(for no)...\n";
				char ans;
				cin >> ans;
				if (ans == 'y')
				{
					array_print(arr, n, m);
				}
			}
			else
			{
				array_print(arr, n, m);
			}
			//Удаление динамического массива.
			for (short int i = 0; i < n; i++)
			{
				delete[] arr[i];
			}
			delete[] arr;
		}
		//Проверка на повторный запуск программы.
		cout << "Run this program again now? (y/n) (one lowercase letter and 'Enter')\n";
		cin >> end;
	}
	return 0;
}