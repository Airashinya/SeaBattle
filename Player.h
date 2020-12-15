#pragma once
#include "stdafx.h"
using namespace std;

class Game;		//объявление прототипа класса Game для дружественного доступа класса Game к классу Player

//******КЛАСС Player******
class Player
{
	//protected:
	char battle_field_arr[10][10];		//arr - двумерный динамический массив для поля боя 
	char hiden_sea_battle[10][10];		//скрытое поле боя на котором находятся корабли
	string name;						//имя
	int num_ship;						//общее количество кораблей
	vector<SHIP> ships;					//хранение всех кораблей
public:
	Player() {}
	Player(string name)
	{
		//заполнение поля
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				hiden_sea_battle[i][j] = tag_sea;
				battle_field_arr[i][j] = tag_sea;
			}
		}
		this->name = name;
		num_ship = 0;
	}
	~Player() {}

	//**********МЕТОДЫ**********
	//вывод скрытого поля боя 
	void show_sea_battle_hidden_player();
	//**********РАССТАНОВКА КОРАБЛЕЙ**********
	//*****RAND*****
	//для установки одного корабля
	vector<SHIP> set_ship_rand(int size_deck);
	//проверяет касается ли корабль другого + 1 ячейке
	bool inspection_of_the_ship_at_the_touch(int x, int y, direction dir, int size_deck);
	//установить все корабли
	void all_set_ships_rand();
	//*****MANUALLY*****
	//размещает один корабль
	vector<SHIP> set_ship_manually(int size_deck);
	//ручная расстановка всех кораблей кораблей
	void all_set_ships_manually();

	//дружественный класс
	friend class Game;
	
	//******************ПЕРЕГРУЗКА ВВОДА/ВЫВОДА******************
	friend ostream& operator << (ostream&stream, Player& obj);
	friend istream& operator >> (istream&stream, Player& obj);
};

