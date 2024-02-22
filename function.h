#pragma once
#include<iostream>
#include<iomanip>
#include<Windows.h>


using namespace std;

enum Color
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void SetColor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template< class T>
void addElem(T*& arr, int& size, T elem)
{
	T* _new = new T[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		_new[i] = arr[i];
	}
	_new[size] = elem;
	size++;
	delete[] arr;
	arr = _new;
}
