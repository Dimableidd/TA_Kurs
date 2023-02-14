#include <iostream>
#include "fstream"
using namespace std;

int Size; // Размер алфавита 
int NS;  // Количество состояний
int FS; // Начальное состояние
bool* ArrS; // Массив состояний
char* Alphabet; // Массив алфавита
int** TT; // Матрица переходов

void Avtomat() // Функция для записи информации об автомате из файла
	{
		ifstream avtomat("avtomat.txt");
		avtomat >> Size; // Чтение из файла размера алфавита
		Alphabet = new char[Size];
		for (int i = 0; i < Size; i++) // Чтение алфавита
			avtomat >> Alphabet[i];
		avtomat >> NS; // Чтение количества состояний
		avtomat >> FS; // Чтение начального состояния
		ArrS = new bool[NS]; 
		for (int i = 0; i < NS; i++) // Чтение массива состояний
			avtomat >> ArrS[i];
		TT = new int* [NS]; // Чтение таблицы переходов
		for (int i = 0; i < NS; i++)
			TT[i] = new int[Size];
		for (int i = 0; i < NS; i++)
			for (int j = 0; j < Size; j++)
				avtomat >> TT[i][j];
		avtomat.close();
	}

void PrintAvtomat() // Вывод введённого автомата
	{
	cout << "  ";
	for (int i = 0; i < Size; i++)
		cout << Alphabet[i] << " ";
	cout << "\n";
	for (int i = 0; i < NS; i++)
	{
		cout << i << " ";
		for (int j = 0; j < Size; j++)
			cout << TT[i][j] << " ";
		cout << ArrS[i] << "\n";
	}
	cout << "\n";
	}

bool Cepb() // Введение цепочки в автомат
	{
		ifstream Cepb("cep.txt");
		int TS = FS; // Запись текущего состояния
		char CS; // Текущий символ
		int NA; // Номер "символа" в алфавите
		while (Cepb && Cepb.peek() != EOF) // Цикл перехода по цепочке
		{
			Cepb >> CS; // Чтение символа из цепочки
			NA = -1; 
			for (int i = 0; i < Size; i++) // Проверка на наличие символа в алфавите
				if (CS == Alphabet[i])
				{
					NA = i;
					break;
				}
			if (NA == -1)
				return 0;
			TS = TT[TS][NA]; // Переход в следующее состояние
		}
		Cepb.close();
		return ArrS[TS];
	}

void main()
{
	setlocale(LC_ALL, "Russian");
	Avtomat();
	PrintAvtomat();
	if (Cepb())
		cout << "True  –  " << "Автомат допускает заданную цепочку" << "\n";
	else
		cout << "False  –  "<< "Автомат отвергает заданную цепочку" << "\n";
}
