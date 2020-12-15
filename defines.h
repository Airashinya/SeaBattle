#pragma once
//****************ПОЛОЖЕНИЕ КОРАБЛЯ****************
enum direction { HORIZONTAL, VERTICAL };


//**********DEFINES**********
	//размер поля
#define COLUMNS 10
#define ROWS 10
	//обозначения в игре
#define ship char(251)		//корабль
#define bomb char(253)		//бомба
#define hit char(229)		//попадание
#define tag_sea char(177)	//море

//**********ЦВЕТА**********
enum ConsoleColor
{
	Black = 0,				//черный
	Blue = 1,				//синий
	Green = 2,				//зеленый
	Cyan = 3,				//темно - бирюзовый
	Red = 4,				//красный
	Magenta = 5,			//пурпурный
	Brown = 6,				//коричневый
	LightGray = 7,			//светло - серый
	DarkGray = 8,			//темно - серый
	LightBlue = 9,			//светло - синий
	LightGreen = 10,		//светло - зеленый
	LightCyan = 11,			//светло - бирюзовый
	LightRed = 12,			//светло - красный
	LightMagenta = 13,		//светло - пурпурный
	Yellow = 14,			//желтый
	White = 15				//белый
};
