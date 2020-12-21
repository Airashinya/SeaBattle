#pragma once
#include "stdafx.h"

//*********ПРЕДИКАТ*********
//Предикат для поиска итератора подбитого корабля 
class PREDICAT_downed_ship
{
	int x;		//строка
	int y;		//столбец
public:
	PREDICAT_downed_ship(int _x, int _y) : x(_x), y(_y) {}

	bool operator()(SHIP obj)
	{
		//если положение корабль вертикальное
		if (obj.dir_n == VERTICAL)
		{
			//диапазон координат корабля между носом корабля и концом корабля
			return ((x >= obj.x_begin && y == obj.y_begin) && (x <= obj.x_end && y == obj.y_end));
		}
		//если положение корабль горизонтальное
		else if (obj.dir_n == HORIZONTAL)
		{
			//диапазон координат корабля между носом корабля и концом корабля
			return ((x == obj.x_begin && y >= obj.y_begin) && (x == obj.x_end && y <= obj.y_end));
		}
	}
};
