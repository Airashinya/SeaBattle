#pragma once
#include "stdafx.h"

//***************ПЕРЕВОД БУКВЫ В ЦИФРУ ПРИ ВВОДЕ КООРДИНАТ***************
int check_input_symb(char column)
{
	int tmp;
	

if (column == 'a' || column == 'A')
		tmp = 0;
	else if (column == 'b' || column == 'B')
		tmp = 1;
	else if (column == 'c' || column == 'C')
		tmp = 2;
	else if (column == 'd' || column == 'D')
		tmp = 3;
	else if (column == 'e' || column == 'E')
		tmp = 4;
	else if (column == 'f' || column == 'F')
		tmp = 5;
	else if (column == 'g' || column == 'G')
		tmp = 6;
	else if (column == 'h' || column == 'H')
		tmp = 7;
	else if (column == 'i' || column == 'I')
		tmp = 8;
	else if (column == 'j' || column == 'J')
		tmp = 9;

	//return tolower(column) - 'a';	//без проверки на ввод русских букв
	return tmp;
}
//функция позволяет менять цвет изображений в консоли
void MyColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//****************ПОЛЕ БОЯ****************
//верхняя строка
void put_top_line(ostream& stream)
{
	stream << "\t\t  " << '|';	//левый верхний угол поля
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << '-' << '|';	//строка
	}
	stream << '-' << "|" << endl;	//првый верхний угол поля 
}
//внутренния строки 
void put_middle_line(ostream& stream)
{
	stream << "\t\t  " << '|';		//первый символ строки
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << '-' << '+';	//строка
	}
	stream << '-' << '|' << endl;	//последний символ строки + перевод
}
//нижняя строка
void put_bottom_line(ostream& stream)
{
	stream << "\t\t  " << '|';	//нижний левый угол
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << '-' << '|';		//строка
	}
	stream << '-' << '|' << endl;	//нижний правый угол
}
//вывод поля
ostream& battlefield(ostream&stream, char arr[][COLUMNS], char *name)
{
	MyColor(Yellow, LightBlue);
	stream << endl << endl;
	stream << "\t\t   A B C D E F G H I J " << endl;
	MyColor(LightCyan, LightBlue);
	put_top_line(stream);				//вывод верхнее строки
	for (int i = 0; i < ROWS; i++)
	{
		MyColor(Yellow, LightBlue);	//номера строк в синем цвете
		stream << "\t\t" << setw(2) << i + 1;	//вывод номера строки
		MyColor(LightCyan, LightBlue);			//цвет поля 
		for (int j = 0; j < COLUMNS; j++)
		{
			//встречает корабль
			if (arr[i][j] == ship)
			{
				stream << '|';			//разделение между ячейками
				MyColor(Green, LightBlue);		//зелёный цвет корабля
				stream << arr[i][j];			//сам корабля
				MyColor(LightCyan, LightBlue);		//возвращаем цвет поля
			}
			//встречает поражение по кораблю
			else if (arr[i][j] == hit)
			{
				stream << '|';		//резделение между ячейкаами
				MyColor(LightRed, LightBlue);		//крассный цвет метки поражения
				stream << arr[i][j];		//вывод метки поражения
				MyColor(LightCyan, LightBlue);	//возвращаем цвет поля
			}
			//встречает бомбу
			else if (arr[i][j] == bomb)
			{
				stream << '|';		//резделение между ячейкаами
				MyColor(DarkGray, LightBlue);	//темно - серый цвет бомбы
				stream << arr[i][j];		//вывод бомбы
				MyColor(LightCyan, LightBlue);	//возвращаем цвет поля
			}
			//в любом другом случае
			else {
				MyColor(LightCyan, LightBlue);			//цвет поля
				stream << '|' << arr[i][j];	//вывод разделения ячеек + ячейка
			}
		}
		stream << '|';	//резделение ячеек
								//номер строки
		if (i == 0)
		{
			MyColor(Magenta, LightBlue);			//пурпурный цвет
			stream << "\t\t" << name << endl;	//вывод имени игрока
			MyColor(LightCyan, LightBlue);			//возвращаем цвет поля
		}
		else
		{
			stream << endl;
		}
		if (i < 9)
			put_middle_line(stream);	//вывод строк между верхней и нижней
	}
	put_bottom_line(stream);	//вывод нижней строки

	return stream;
}

