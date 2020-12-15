#pragma once
#include "stdafx.h"

//***************ѕ≈–≈¬ќƒ Ѕ” ¬џ ¬ ÷»‘–” ѕ–» ¬¬ќƒ≈  ќќ–ƒ»Ќј“***************
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
//функци€ позвол€ет мен€ть цвет изображений в консоли
void MyColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//****************ѕќЋ≈ Ѕќя****************
//верхн€€ строка
void put_top_line(ostream& stream)
{
	stream << "\t\t  " << char(201);	//левый верхний угол пол€
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(203);	//строка
	}
	stream << char(205) << char(187) << endl;	//првый верхний угол пол€ 
}
//внутренни€ строки 
void put_middle_line(ostream& stream)
{
	stream << "\t\t  " << char(204);		//первый символ строки
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(206);	//строка
	}
	stream << char(205) << char(185) << endl;	//последний символ строки + перевод
}
//нижн€€ строка
void put_bottom_line(ostream& stream)
{
	stream << "\t\t  " << char(200);	//нижний левый угол
	for (int i = 0; i < COLUMNS - 1; i++)
	{
		stream << char(205) << char(202);		//строка
	}
	stream << char(205) << char(188) << endl;	//нижний правый угол
}
//вывод пол€
ostream& battlefield(ostream&stream, char arr[][COLUMNS], char *name)
{
	MyColor(Yellow, Black);
	stream << endl << endl;
	stream << "\t\t   A B C D E F G H I J " << endl;
	MyColor(LightCyan, Black);
	put_top_line(stream);				//вывод верхнее строки
	for (int i = 0; i < ROWS; i++)
	{
		MyColor(Yellow, Black);	//номера строк в синем цвете
		stream << "\t\t" << setw(2) << i + 1;	//вывод номера строки
		MyColor(LightCyan, Black);			//цвет пол€ 
		for (int j = 0; j < COLUMNS; j++)
		{
			//встречает корабль
			if (arr[i][j] == ship)
			{
				stream << char(186);			//разделение между €чейками
				MyColor(LightGreen, Black);		//зелЄный цвет корабл€
				stream << arr[i][j];			//сам корабл€
				MyColor(LightCyan, Black);		//возвращаем цвет пол€
			}
			//встречает поражение по кораблю
			else if (arr[i][j] == hit)
			{
				stream << char(186);		//резделение между €чейкаами
				MyColor(LightRed, Black);		//крассный цвет метки поражени€
				stream << arr[i][j];		//вывод метки поражени€
				MyColor(LightCyan, Black);	//возвращаем цвет пол€
			}
			//встречает бомбу
			else if (arr[i][j] == bomb)
			{
				stream << char(186);		//резделение между €чейкаами
				MyColor(DarkGray, Black);	//темно - серый цвет бомбы
				stream << arr[i][j];		//вывод бомбы
				MyColor(LightCyan, Black);	//возвращаем цвет пол€
			}
			//в любом другом случае
			else {
				MyColor(LightCyan, Black);			//цвет пол€
				stream << char(186) << arr[i][j];	//вывод разделени€ €чеек + €чейка
			}
		}
		stream << char(186);	//резделение €чеек
								//номер строки
		if (i == 0)
		{
			MyColor(Magenta, Black);			//пурпурный цвет
			stream << "\t\t" << name << endl;	//вывод имени игрока
			MyColor(LightCyan, Black);			//возвращаем цвет пол€
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

