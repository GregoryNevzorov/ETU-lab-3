#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	char end = 'y';
	while (end == 'y')
	{
		short int n, m; //Пользовательская размерность массива
		cout << "Only the matrix with the number of elements is less than 130 million.\n\n";
		cout << "Enter the number of rows in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < input <= 32767\n";
		cin >> n;
		cout << "Enter the number of columns in the matrix: (use for input only arabic numeral 0-9)\n";
		cout << "0 < input <= 32767\n";
		cin >> m;

		long int amount_of_elements = n * m;

		MEMORYSTATUSEX ms;
		ms.dwLength = sizeof(ms);
		GlobalMemoryStatusEx(&ms);
		cout << (ms.ullTotalPhys / 1024 / 1024) << " Mbyte\n";
		cout << (ms.ullAvailPhys / 1024 / 1024) << " Mbyte\n";

		if (amount_of_elements > ((ms.ullAvailPhys / 4) - (256 * 1024 * 1024))) //256 Мб в запасе.
		{
			cout << "Only the matrix with the number of elements is less than 130 million.\n";
			//Проверка на повторный запуск программы.
			cout << "Run this program again now? (y/n) (one lowercase letter and 'Enter')\n";
			cin >> end;
		}
		else
		{
			long int* arr;
			arr = new long int[amount_of_elements];

			delete[] arr;

			//Проверка на повторный запуск программы.
			cout << "Run this program again now? (y/n) (one lowercase letter and 'Enter')\n";
			cin >> end;
		}
	}
	return 0;
}
