#include <iostream>
#include "fstream"
using namespace std;

int Size; // ������ �������� 
int NS;  // ���������� ���������
int FS; // ��������� ���������
bool* ArrS; // ������ ���������
char* Alphabet; // ������ ��������
int** TT; // ������� ���������

void Avtomat() // ������� ��� ������ ���������� �� �������� �� �����
	{
		ifstream avtomat("avtomat.txt");
		avtomat >> Size; // ������ �� ����� ������� ��������
		Alphabet = new char[Size];
		for (int i = 0; i < Size; i++) // ������ ��������
			avtomat >> Alphabet[i];
		avtomat >> NS; // ������ ���������� ���������
		avtomat >> FS; // ������ ���������� ���������
		ArrS = new bool[NS]; 
		for (int i = 0; i < NS; i++) // ������ ������� ���������
			avtomat >> ArrS[i];
		TT = new int* [NS]; // ������ ������� ���������
		for (int i = 0; i < NS; i++)
			TT[i] = new int[Size];
		for (int i = 0; i < NS; i++)
			for (int j = 0; j < Size; j++)
				avtomat >> TT[i][j];
		avtomat.close();
	}

void PrintAvtomat() // ����� ��������� ��������
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

bool Cepb() // �������� ������� � �������
	{
		ifstream Cepb("cep.txt");
		int TS = FS; // ������ �������� ���������
		char CS; // ������� ������
		int NA; // ����� "�������" � ��������
		while (Cepb && Cepb.peek() != EOF) // ���� �������� �� �������
		{
			Cepb >> CS; // ������ ������� �� �������
			NA = -1; 
			for (int i = 0; i < Size; i++) // �������� �� ������� ������� � ��������
				if (CS == Alphabet[i])
				{
					NA = i;
					break;
				}
			if (NA == -1)
				return 0;
			TS = TT[TS][NA]; // ������� � ��������� ���������
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
		cout << "True  �  " << "������� ��������� �������� �������" << "\n";
	else
		cout << "False  �  "<< "������� ��������� �������� �������" << "\n";
}
