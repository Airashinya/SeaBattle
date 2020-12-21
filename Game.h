#pragma once
#include "stdafx.h"


//*********КЛАСС GAME**********
class Game
{
	bool new_generate_koordinat;	//для позволения генерации новых координат
	int _x_;		//строка  1 >< 10
	int _y_;		//столбец A >< J
	bool alive_ship_on_which_the_last_hit;		//для определения жизни корабля по которому был последний выстрел, 
												//чтобы определить продолжать ли стрелять компу по этому кораблю
public:
	Game() 
	{
		new_generate_koordinat = true;
		alive_ship_on_which_the_last_hit = false;
		_x_ = _y_ = 0;
	}
	~Game() {}
	//***************************
	//start battle time
	void timer_start_battle();
	//метод показа обозначений в игре
	void designations_in_game();

	//******************ИГРА******************
	//метод игры Player vs Player 
	void Player_vs_Player(Player player1OBJ, Player player2OBJ);
	//метод игры COMP vs Player
	void COMP_vs_Player(Player compOBJ, Player playerOBJ);
	//метод игры Player vs COMP
	void Player_vs_COMP(Player playerOBJ, Player compOBJ);
	//начало игры
	void start_game();

};
