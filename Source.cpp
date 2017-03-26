
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ofstream file("log.txt");
struct cell
{
	int x, y, value;
};

//Отчистка массива
void clear(int **arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		arr[i] = new int[n];
		arr[0][i] = i;
		arr[i][0] = i;
	}
	for (int i = 1; i < n; ++i)
		for (int j = 1; j < n; ++j)
			arr[i][j] = -1;
}

//Функция проверки возможности постановки клетки
bool place(int **arr, int n, cell c)
{
	for (int i = 0; i < c.x; ++i)
	{
		if (c.value == arr[c.y][i]) return false;
	}
	for (int i = 0; i < c.y; ++i)
	{
		if (c.value == arr[i][c.x]) return false;
	}
	return true;
}

//Показывает массив
void show(int **arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
//Вывести массив
void show(int **arr, int n, ofstream &file)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			file << arr[i][j] << ' ';
		}
		file << endl;
	}
	file << endl;
}
//Создает в заданном массиве приведенный латинский квадрат
void create(int **arr, int n, cell c, int &kol)
{
	if (!place(arr, n, c)) // проверка возможности подстановки
		return;
	arr[c.y][c.x] = c.value; //новое частичное решение
	//show(arr, n); 
	show(arr, n, file); 
	cell new_c = c;
	++new_c.x;
	if (new_c.x == n) //перход на первую вертикаль
	{
		new_c.x = 1;
		++new_c.y;
		if (new_c.y == n) //переход на новую горизонталь
		{
			show(arr, n);
			++kol;
			arr[c.y][c.x] = -1;
			return;
		}
	}
	int i = 0;
	do //заполнение массива
	{
		new_c.value = (new_c.value + 1) % n;
		create(arr, n, new_c, kol); // создание нового решения
		++i;
	} while (i != n);
	arr[c.y][c.x] = -1;
	return;
}

int main(){
	setlocale(LC_ALL, "Rus");
	int n, kol = 0, fileMode=0;
	cout << "Выберите откуда брать входные данные. " << endl;
	cout << "1 - из консоли" << endl;
	cout << "2 - из файла" << endl;
	cin >> fileMode;
	while (!cin) {
		cout << "Не нужно вводить буквы. Попробуйте ещё раз" << endl;
		cin.clear();
		while (cin.get() != '\n');
		cin >> fileMode;
	}
	if (fileMode == 1) {
		cout << "Введите n" << endl;
		cin >> n;
		while (!cin) {
			cout << "Не нужно вводить буквы. Попробуйте ещё раз" << endl;
			cin.clear();
			while (cin.get() != '\n');
			cin >> n;
		}
		if (n<0)
		{
			cout << "Зачем вы ввели отрицательное число?" << endl;
			while (n < 0) {
				cout << "Введите размер массива снова" << endl;
				cin >> n;
			}
		}
		if (n>=8)
		{
			cout << "Извините, число решений слишком большое. " << endl << "Вы всё равно не запомните."<<endl;
			while (n >=8) {
				cout << "Введите размер поменьше" << endl;
				cin >> n;
			}
		}
		if ( n < 8 && n>0)
		{

			int **arr = new int*[n];
			for (int i = 0; i < n; ++i)
			{
				clear(arr, n);
				create(arr, n, { 1,1,i }, kol);
			}
			cout << endl << "Число приведенных латинских квадратов: " << kol << endl;
			system("pause");
			return 0;
		}
	
	}
		if (fileMode == 2){
			ifstream fin;
			cout << "Введите путь к файлу" << endl;
			string path;
			cin >> path;
			fin.open(path);
			if ((fin >> n) && n<8 && n>2){
			cout << "Введенный размер квадратной матрицы: " << n << endl;
			
				int **arr = new int*[n];
				for (int i = 0; i < n; ++i)
				{
					clear(arr, n);
					create(arr, n, { 1,1,i }, kol);
				}
				cout << endl << "Число приведенных латинских квадратов: " << kol << endl;
				system("pause");
				return 0;
			}
	
	}

	system("pause");
	return 0;
}