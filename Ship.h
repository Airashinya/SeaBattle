#pragma once
#include "stdafx.h"
#include "defines.h"

//*****КЛАСС КОРАБЛЬ*****
class SHIP
{
public:
	//координаты корабля
	int x_begin;	//координата начала корабля по строке
	int y_begin;	//координата начала корабля по столбцу
	int x_end;		//координата конца корабля по столбцу
	int y_end;		//координата конца корабля по столбцу

	bool alive;	//состояние корабля
	int num_deck_ship;	//количество палуб
	char *new_ship;		//для создания корабля
	direction dir_n;	//положение корабля
	int num_shot;			//количество попадений по кораблю

	SHIP() {}
	SHIP(int _x_begin, int _y_begin, int _x_end, int _y_end, int _deck, bool _is_dead, direction _dir_on)
	{
		x_begin = _x_begin;
		y_begin = _y_begin;
		x_end = _x_end;
		y_end = _y_end;
		num_deck_ship = _deck;
		alive = true;
		new_ship = new char[_deck];
		dir_n = _dir_on;
		num_shot = 0;
		for (int i = 0; i < _deck; i++)
			new_ship[i] = ship;
	}
	~SHIP() {}
	//мертвая зона корабля
	void dead_zone_the_ship(char arr[][COLUMNS], bool _is_dead, direction dir_n);
};