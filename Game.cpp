#include "stdafx.h"

//******************РЕЖИМЫ ИГРЫ******************
//метод игры Player1 vs Player2
void Game::Player_vs_Player(Player player1OBJ, Player player2OBJ)
{
	system("cls");
	//вывод скрытого поля боя с кораблями Игрок
	player1OBJ.show_sea_battle_hidden_player();
	//вывод поля боя Комп
	cout << player2OBJ << endl;
	//показывает чей ход
	cout << "Goes " << player1OBJ.name << endl;
	cout << "Enter koordinat A1 > J10: ";

	int row = 0;
	char column = ' ';

	//проверка на наличие кораблей
	if (player1OBJ.num_ship == 0)
	{
		system("cls");			//очистка экрана
		MyColor(LightRed, Black);		//красный цвет
		cout << player1OBJ.name << ", LOSE!!! " << endl;	//у вас не осталось кораблей, вы проиграли
		MyColor(LightCyan, Black);			//светло - бирюзовый цвет
		cout << endl << endl << "Press any key to continue " << endl;		//нажать любую клавишу для продолжения
		Sleep(4000);			//задержка 4 сек
		start_game();			//заново вызов игры
	}else if (player1OBJ.num_ship > 0)
	{
		//проверка на ввод координат
		do
		{
			//пока не будет введен символ, цикл будет повторяться
			do
			{
				cin >> column;		//вводим буквы (координата)
			}while(isdigit(column));
			//пока не будет введена цифра (координата)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
			//диапазон проверки на ввод (tolower - меняет регистр введенной буквы)
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//преобразование номера ячейки массива для выстрела Буква -> цифру
		int tmp = check_input_symb(column);	//перевод введенной буквы координат в цифру 

		row -= 1;	//вычитаем -1 так как нумерациия ячеек массива с 0


		//если текущая метка поражена попадением
		if (player2OBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "The ship had been struck " << endl;		//корабль уже был поражен
			Sleep(1500);			//задержка 1.5 сек
			cout << "Goes, " << player1OBJ.name << endl;
			Player_vs_Player(player1OBJ, player2OBJ);			//ход игрок1
			system("cls");			//очистка экрана
		}
		//если текущая метка была поражена мимо
		else if (player2OBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "We have a shot at this place " << endl;	//вы уже стреляли в это место
			Sleep(1500);				//задержка 1.5 сек
			cout << "Goes, " << player1OBJ.name << endl;
			system("cls");				//очистка экрана
			Player_vs_Player(player1OBJ, player2OBJ);			//ход игрок1
		}
		//если текущая метка пуста
		else if (player2OBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "PAST! " << endl;			//вывод "МИМО"
			player2OBJ.battle_field_arr[row][tmp] = bomb;			//ставим бомбу на основном поле
			player2OBJ.hiden_sea_battle[row][tmp] = bomb;			//ставим бомбу на скрытом поле
			Sleep(1500);				//задержка 1.5 сек
			cout << "Goes, " << player2OBJ.name << endl;			//
			system("cls");
			Player_vs_Player(player2OBJ, player1OBJ);			//ход игрок2
		}
		//если на текущей метке корабль
		else if (player2OBJ.hiden_sea_battle[row][tmp] == ship)
		{
			player2OBJ.battle_field_arr[row][tmp] = hit;			//ставим метка попадания на основном поле
			player2OBJ.hiden_sea_battle[row][tmp] = hit;			//ставим метка попадания на скрытом поле

			//итератор для возврата корабля по которому попали
			vector<SHIP>::iterator _itShips = find_if(player2OBJ.ships.begin(), player2OBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//вернули итератор на корабль по которому попали 
			if (_itShips != player2OBJ.ships.end())
			{
				_itShips->num_shot++;				//+1 к количеству попаданий
				//если количество попаданий равняется количеству палуб
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, Black);		//красный цвет
					cout << "KILL" << endl;			//вывод "УБИТ"
					player2OBJ.num_ship--;		//-1 от количества корабля игрока
					_itShips->alive = false;	//корабль мёртв 
					_itShips->dead_zone_the_ship(player2OBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//отрисовка мертвой зоны корабля на скрытом поле боя
					_itShips->dead_zone_the_ship(player2OBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//отрисовка мертвой зоны корабля на основном поле боя
				}else
				{
					MyColor(Yellow, Black);			//жёлтый цвет
					cout << "STRUCK " << endl;		//вывод "ПОПАЛ"
				}
			}

			Sleep(1000);			//задержка 1 сек
			system("cls");			//очистка экрана
			//получает еще один ход
			Player_vs_Player(player1OBJ, player2OBJ);				//ход игрок1
		}
	}
}
//метод игры COMP vs Player (ход компьютер)
void Game::COMP_vs_Player(Player compOBJ, Player playerOBJ)
{
	system("cls");
	compOBJ.show_sea_battle_hidden_player();		//показ скрытого поля боя компа
	
		//если количество кораблей Игрока 0, то он проиграл 
		if (playerOBJ.num_ship == 0)
		{
			system("cls");					//очистка экрана
			playerOBJ.show_sea_battle_hidden_player();
			MyColor(LightRed, Black);		//светло - красный цвет
			cout << playerOBJ.name << ", LOSE!!! " << endl;	//у вас не осталось кораблей, вы проиграли
			MyColor(LightCyan, Black);		//светло - бирюзовый
			Sleep(4000);			//задержка 4 сек
			start_game();			//вызов игры заново
		}
	
		//проверка на наличие кораблей
		else if (compOBJ.num_ship > 0)
		{
		//генерирование координат
			//если true, то генерируем
			//если false, то остаются прежние координаты для продолжения стрельбы по подбитому кораблю
			if (new_generate_koordinat == true)
			{
				_x_ = rand() % 10;
				_y_ = rand() % 10;
				new_generate_koordinat = false;		//запрет новой генерации
			}

			//если текущая метка поражена попадением	(проверка на показательном поле)
			if (playerOBJ.battle_field_arr[_x_][_y_] == hit && alive_ship_on_which_the_last_hit == false)
			{
				system("cls");						//очистка экрана
				new_generate_koordinat = true;		//разрешить генерацию новых координат
				COMP_vs_Player(compOBJ, playerOBJ);		//ход компа
			}
			//если текущая метка была поражена мимо	(проверка на показательном поле)
			else if (playerOBJ.battle_field_arr[_x_][_y_] == bomb)
			{
				system("cls");							//очистка экрана
				new_generate_koordinat = true;			//разрешить генерацию новых координат
				COMP_vs_Player(compOBJ, playerOBJ);		//ход компа
			}
			//если текущая метка пуста	(проверка на показательном поле)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == tag_sea)
			{
				if (playerOBJ.hiden_sea_battle[_x_][_y_] != ship && 
					playerOBJ.hiden_sea_battle[_x_][_y_] != hit){
				playerOBJ.battle_field_arr[_x_][_y_] = bomb;		//поставить бомбу на текущей ячейке, на основном поле боя
				playerOBJ.hiden_sea_battle[_x_][_y_] = bomb;		//поставить бомбу на текущей ячейке, на скрытом поле боя
				}
				system("cls");								//очистка экрана
				new_generate_koordinat = true;				//разрешить генерацию новых координат
				Player_vs_COMP(playerOBJ, compOBJ);			//ход игрок
			}
			//если на текущей метке корабль	(проверка на скрытом поле)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == ship || alive_ship_on_which_the_last_hit == true)
			{
				playerOBJ.battle_field_arr[_x_][_y_] = hit;		//поставить метку поражения при попадении на основном поле боя
				playerOBJ.hiden_sea_battle[_x_][_y_] = hit;		//поставить метку поражения при попадении на скрытом поле боя
				system("cls");			//очистка экрана
				playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя
				MyColor(Yellow, Black);			//желтый цвет
				cout << "STRUCK " << endl;		//вывод на экран "ПОПАЛ"
				Sleep(500);			//задержка 0.5 сек	

				//итератор для возврата корабля по которому попали
				vector<SHIP>::iterator _itShips = find_if(playerOBJ.ships.begin(), playerOBJ.ships.end(), PREDICAT_downed_ship(_x_, _y_));
				//вернули итератор
				if (_itShips != playerOBJ.ships.end())
				{
					if (alive_ship_on_which_the_last_hit == false)
						_itShips->num_shot++;			//+1 к попаданиям
					//если попадение было по последней палубе, то корабль убит и переходим к новой генерации координат
					if (_itShips->num_deck_ship == _itShips->num_shot)
					{
						MyColor(LightRed, Black);			//светло - красный цвет
						cout << "KILL " << endl;			//вывод на экран при убийстве "УБИТ"
						_itShips->alive = false;			//отмечаем в векторе данному кораблю УБИТ
						new_generate_koordinat = true;		//разрешить генерацию новых координат
						alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
						playerOBJ.num_ship--;				//-1 корабль от всех кораблей Игрока, при убийстве
						_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, VERTICAL);				//отрисовка мертвой зоны при убийстве (на основном поле)
						_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, VERTICAL);				//отрисовка мертвой зоны при убийстве (на скрытом поле)
						Sleep(500);					//задержка 0.5 сек
						COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
					}	
					//******************************************************************************************************
					
						//запомнили, чтобы менять значение для сдвига влево/вправо
						int tmp_column = _y_;		//запоминаем столбец

						//------------->	стрельба вправо по горизонтали 
						if (_itShips->alive == true && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship  && _y_ + 1 <= COLUMNS - 1)
						{
						
							//пока +1 ячейка корабль
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship)
							{
								_itShips->num_shot++;		//+1 к попадаениям
								playerOBJ.battle_field_arr[_x_][tmp_column + 1] = hit;			//на основном поле ставим метку попадания
								playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = hit;			//на скрытом поле ставим метку попадания
								system("cls");				//очистка экрана
								playerOBJ.show_sea_battle_hidden_player();		//показ скрытого поля боя
								MyColor(Yellow, Black);					//желтый цвет
								cout << "STRUCK " << endl;				//вывод "ПОПАЛ"
								new_generate_koordinat = false;			//запрет новой генерации координат
								Sleep(1000);			//задержка 1 сек
								tmp_column += 1;		//сдвиг вправо на 1 ячейку
							}
								//если количество попаданий по кораблю равняется количеству палуб 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);			//красный цвет
									cout << "KILL" << endl;				//вывод "УБИТ"
									playerOBJ.num_ship--;				//-1 от количества кораблей игрока
									_itShips->alive = false;			//корабль мёртв
									new_generate_koordinat = true;		//разрешить генерировать новые координаты для выстрела
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//отрисовка мертвой зоны на скрытом поле боя 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//отрисовка мертвой зоны на основном поле боя 
									Sleep(1000);				//задержка 1 сек
									system("cls");				//очистка экрана
									playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя
								}
							//если корабль упирается в правый край и жив
							if (_itShips->y_end == COLUMNS - 1 && _itShips->alive == true)
							{
								new_generate_koordinat = false;					//запрет новой генерации координат
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								COMP_vs_Player(compOBJ, playerOBJ);		//ход компа
							}
								//если корабль упирается в правый край и мёртв
							else if (_itShips->y_end == COLUMNS - 1  && _itShips->alive == false)
							{
								new_generate_koordinat = true;			//разрешить генерировать новые координаты для выстрела
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								COMP_vs_Player(compOBJ, playerOBJ);		//ход компа
							}
								//если корабль не упирается в правый край и жив
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column + 1] = bomb;			//на основном поле боя ставим бомбу
									playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = bomb;			//на скрытом поле боя ставим бомбу
								}
								new_generate_koordinat = false;			//запрет новой генерации координат
								Player_vs_COMP(playerOBJ, compOBJ);		//ход игрока
							}		
								//если корабль не упирается в правый край и мёртв
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;			//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);		//ход компа
							}
						}
						//******************************************************************************************************
						//<-------------	стрельба влево по горизонтали 
						if (_itShips->alive == true && new_generate_koordinat == false && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship  && _y_ - 1 >= 0)
						{
						
							//пока +1 ячейка корабль
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship)
							{
								_itShips->num_shot++;				//+1 к количеству попадений по кораблю
								playerOBJ.battle_field_arr[_x_][tmp_column - 1] = hit;			//на основном поле ставим метку попадания
								playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = hit;			//на скрытом поле ставим метку попадания
								system("cls");					//очистка экрана
								playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя
								MyColor(Yellow, Black);			//желтый цвет
								cout << "STRUCK " << endl;			//вывод "ПОПАЛ"
								new_generate_koordinat = false;			//запрет новой генерации координат
								Sleep(500);			//задержка 0.5 сек
								tmp_column -= 1;			//сдвиг влево
							}
							//если количество попаданий по кораблю равняется количеству палуб 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);				//красный цвет
									cout << "KILL" << endl;				//вывод "УБИТ"
									playerOBJ.num_ship--;				//-1 от количества кораблей 
									_itShips->alive = false;			//отмечаем, что корабль мёртв
									new_generate_koordinat = true;		//разрешить генерировать новые координаты для выстрела
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//отрисовка мертвой зоны на скрытом поле боя 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//отрисовка мертвой зоны на основном поле боя 
									Sleep(1000);				//задержка 1 сек
									system("cls");				//очистка экрана
									playerOBJ.show_sea_battle_hidden_player();				//показ скрытого поля боя 
								}
							//если корабль упирается в левый край и жив
							if (_itShips->y_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;					//запрет новой генерации координат
								COMP_vs_Player(compOBJ, playerOBJ);				//ход компа
							}
								//если корабль упирается в левый край и мёртв
							else if (_itShips->y_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;					//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);				//ход компа
							}
								//если корабль не упирается в левый край и жив
							else if (_itShips->y_begin - 1 > 0  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;								//запрет новой генерации координат
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column - 1] = bomb;		//на - 1 ячейке ставим бомбу (на основном поле)
									playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = bomb;		//на - 1 ячейке ставим бомбу (на скрытом поле)
								}
								Player_vs_COMP(playerOBJ, compOBJ);							//ход игрока
							}
								//если корабль не упирается в левый край и мёртв
							else if (_itShips->y_begin - 1 >= 0  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;							//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);						//ход компа
							}
						}
			//******************************************************************************************************
						//запомнили, чтобы именять значение для сдвига вверх/вниз
						int tmp_row = _x_;			//запомнить координату строки
					
						// |
						// |
						// |
						// |
						// |
						//\_/
						//стрельба вниз по вертикали
						if (_itShips->alive == true && _itShips->dir_n == VERTICAL &&
							playerOBJ.hiden_sea_battle[_x_ + 1][_y_] == ship && _x_ + 1 <= ROWS - 1)
						{
							//пока +1 ячейка корабль
							while (playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 к количеств попаданий по кораблю
								playerOBJ.battle_field_arr[tmp_row + 1][_y_] = hit;			//отмечаем меткой попадания
								playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] = hit;
								system("cls");
								playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя 
								MyColor(Yellow, Black);
								cout << "STRUCK " << endl;	
								new_generate_koordinat = false;			//запрет новой генерации координат
								Sleep(500);
								tmp_row += 1;			//сдвиг вниз
							}
							//если количество попаданий по кораблю равняется количеству палуб 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);
									cout << "KILL" << endl;
									playerOBJ.num_ship--;				//-1 от количества кораблей 
									_itShips->alive = false;			//корабль мертв
									new_generate_koordinat = true;		//разрешить генерировать новые координаты для выстрела
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);				//отрисовка мертвой зоны на скрытом поле боя 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);				//отрисовка мертвой зоны на основном поле боя 
									Sleep(1000);
									system("cls");
									playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя
								}
								//если корабль упирается вниз и жив
							if (_itShips->x_end == ROWS - 1 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;					//запрет новой генерации координат
								COMP_vs_Player(compOBJ, playerOBJ);				//ход компа
							}
								//если корабль упирается вниз и мёртв
							else if (_itShips->x_end == ROWS - 1 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;					//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);				//ход компа
							}
								//если корабль не упирается вниз и жив
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;					//запрет новой генерации координат
								if (playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row + 1][tmp_column] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);		//ход игрока
							}
								//если корабль не упирается вниз и мёртв
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;				//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
							}
						}
			//******************************************************************************************************
						//стрельба вверх по вертикали
						//	 _
						//	/ \
						//	 |
						// 	 |
						//	 |
						//	 |
						//	 |
						if (_itShips->alive == true && _itShips->dir_n == VERTICAL &&
							playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] == ship && _x_ - 1 >= 0)
						{
							//пока +1 ячейка корабль
							while (playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 к количеству попадений по кораблю 
								playerOBJ.battle_field_arr[tmp_row - 1][_y_] = hit;		//на основном поле ставим метку попадания
								playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = hit;		//на скрытом поле ставим метку попадания
								system("cls");				//очистка экрана
								playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя 
								MyColor(Yellow, Black);				//желтый цвет
								cout << "STRUCK " << endl;			//вывод "ПОПАЛ"
								new_generate_koordinat = false;				//запрет новой генерации координат
								Sleep(500);			//задержка 0.5 сек
								tmp_row -= 1;				//сдвиг вверх
							}
							//если количество попаданий по кораблю равняется количеству палуб 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, Black);			//светло - красный цвет
									cout << "KILL" << endl;				//вывод "УБИТ"
									playerOBJ.num_ship--;				//-1 от количества кораблей
									_itShips->alive = false;			//корабль мертв
									new_generate_koordinat = true;		//разрешить генерировать новые координаты для выстрела
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);					//отрисовка мертвой зоны на скрытом поле боя 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);					//отрисовка мертвой зоны на основном поле боя 
									Sleep(1000);				//задержка 1 сек
									system("cls");				//очистка экрана
									playerOBJ.show_sea_battle_hidden_player();			//показ скрытого поля боя 
								}
								//если корабль упирается вверх и жив
							if (_itShips->x_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;				//запрет новой генерации координат
								COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
							}	
								//если корабль упирается вверх и мёртв
							else if (_itShips->x_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;				//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
							}
								//если корабль не упирается вверх и жив
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//говорим, что корабль по которому был выстрел жив
								new_generate_koordinat = false;				//запрет новой генерации координат
								if (playerOBJ.hiden_sea_battle[_x_ - 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row - 1][_y_] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);			//ход игрока
							}
								//если корабль не упирается вверх и мёртв
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//говорим, что корабль по которому был выстрел мертв
								new_generate_koordinat = true;				//разрешить генерировать новые координаты для выстрела
								COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
							}
						}
				}
				COMP_vs_Player(compOBJ, playerOBJ);			//ход компа
			}
	}
}
//метод игры Player vs COMP	(ход игрок)
void Game::Player_vs_COMP(Player player1OBJ, Player compOBJ)
{
	system("cls");
	//вывод скрытого поля боя с кораблями Игрок
	player1OBJ.show_sea_battle_hidden_player();
	//вывод поля боя Комп
	cout << compOBJ << endl;

	cout << "Goes " << player1OBJ.name << endl;
	cout << "Enter koordinat A1 > J10: ";

	int row = 0;
	char column = ' ';

	//проверка на наличие кораблей

	//если количество кораблей Компа 0, то он проиграл
	if (compOBJ.num_ship == 0)
	{
		system("cls");				//очистка экрана
		MyColor(LightRed, Black);			//красный цвет
		cout << compOBJ.name << ", LOSE!!! " << endl;	//у вас не осталось кораблей, вы проиграли
		MyColor(LightCyan, Black);			//светло - бирюзовый
		Sleep(4000);				//задержка 4 сек
		start_game();				//вызов новой игры
	}
	//если количество кораблей больше 0, продолжается игра
	if (player1OBJ.num_ship > 0)
	{
		//проверка на ввод координат
		do
		{
			//пока не будет введен символ, цикл будет повторяться
			do
			{
				cin >> column;		//вводи буквы (координата)
			}while(isdigit(column));
			//пока не будет введена цифра (координата)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//преобразование номера ячейки массива для выстрела Буква -> цифру
		int tmp = check_input_symb(column);	//перевод введенной буквы координат в цифру 

		row -= 1;	//вычитаем -1 так как нумерациия ячеек массива с 0


		//если текущая метка поражена попадением
		if (compOBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "The ship had been struck " << endl;	//корабль уже был поражен
	//		Sleep(1500);		//зажержка 1.5 сек
			cout << "Goes, " << player1OBJ.name << endl;
			Player_vs_COMP(player1OBJ, compOBJ);			//ход игрока
			system("cls");				//очистка экрана
		}
		//если текущая метка была поражена мимо
		else if (compOBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "We have a shot at this place " << endl;	//вы уже стреляли в это место
		//	Sleep(1500);			//задержка 1.5 сек
			cout << "Goes, " << player1OBJ.name << endl;
			system("cls");			//очистка экрана
			Player_vs_COMP(player1OBJ, compOBJ);				//ход игрока
		}
		//если текущая метка пуста
		else if (compOBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "PAST! " << endl;				//вывод "МИМО"
			if (compOBJ.battle_field_arr[row][tmp] != ship){
			compOBJ.battle_field_arr[row][tmp] = bomb;			//ставим бомбу на основном поле
			compOBJ.hiden_sea_battle[row][tmp] = bomb;			//ставим бомбу на основном поле
			}
		//	Sleep(1500);			//задержка 1.5 сек
			cout << "Goes, " << compOBJ.name << endl;
			system("cls");			//очистка экрана
			COMP_vs_Player(compOBJ, player1OBJ);				//ход компа
		}
		//если на текущей метке корабль
		else if (compOBJ.hiden_sea_battle[row][tmp] == ship)
		{
			compOBJ.battle_field_arr[row][tmp] = hit;		//ставим метку попадания на основном поле 
			compOBJ.hiden_sea_battle[row][tmp] = hit;		//ставим метку попадания на основном поле 

			//итератор для возврата корабля по которому попали
			vector<SHIP>::iterator _itShips = find_if(compOBJ.ships.begin(), compOBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//вернули итератор на кораль по которому попали 
			if (_itShips != compOBJ.ships.end())
			{
				_itShips->num_shot++;			//+1 к количеству попадений
				//если количество поподений по кораблю равняется количеству палуб 
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, Black);		//красный цвет
					cout << "KILL" << endl;			//вывод "УБИТ"
					compOBJ.num_ship--;			//-1 от количества кораблей компа
					_itShips->alive = false;	//кораблья мертв
					_itShips->dead_zone_the_ship(compOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//отрисовка мертвой зоны на скрытом поле боя
					_itShips->dead_zone_the_ship(compOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//отрисовка мертвой зоны на основном поле боя
				}else
				{
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "STRUCK " << endl;		//вывод "ПОПАЛ"
				}
			}

			Sleep(1500);			//задержка 1.5 сек 
			system("cls");			//очистка экрана
			//получает еще один ход
			Player_vs_COMP(player1OBJ, compOBJ);			//ход игрока
		}
	}
}
//таймер начала боя
void Game::timer_start_battle()
{
		system("cls");
		for (int i = 3; i >= 1; i--)
		{
			MyColor(LightGreen, Black);		//светло - зеленый цвет
			cout << "\t\t\t\t\t\t\t" << i;	
			Sleep(1000);
			system("cls");
		}
		cout << "\t\t\t\t\t\t  *-*-*[FIGHT]*-*-*" << endl;
		Sleep(1000);
		system("cls");

	}
//обозначения в игре
void Game::designations_in_game()
	{
		//обозначения в игре
		cout << "[The designations in game]" << endl << endl;
		cout << "\tBomb: ";
		MyColor(DarkGray, Black);
		cout << bomb << endl;				//бомба
		MyColor(LightCyan, Black);
		cout << "\tHit : ";
		MyColor(LightRed, Black);
		cout << hit << endl;				//поражение по кораблю
		MyColor(LightCyan, Black);
		cout << "\tShip: ";
		MyColor(LightGreen, Black);
		cout << ship << endl;				//корабль
		MyColor(LightCyan, Black);
		cout << endl << endl << "Press any key to continue " << endl;		//нажать любую клавишу для продолжения
		_getch();			//ждёт нажатия клавиши
		system("cls");
	}
//начало игры
void Game::start_game()
{
	system("cls");			//очистка экрана 
	//**********ЭКЗЕМПЛЯРЫ**********
	Player human1("Player1");			//экземпляр для Игрок1
	Player human2("Player2");			//экземпляр для Игрок2
	SHIP obj_ship;						//экземпляр класса Корабль
	Player comp("COMP");				//экземпляр для COMP
	Game game;							//экземпляр класса Игра

	MyColor(LightCyan, Black);			//светло - бирюзовый
	game.designations_in_game();		//показ обозначений в игре
	

	int selection = 0;	//выбор по менюшке	

	do
	{
		system("cls");				//очистка экрана 
		MyColor(LightCyan, Black);	//светло - бирюзовый цвет
		cout << "[Select game mode] " << endl << endl;
		cout << "\t[1] Player vs Player " << endl;
		cout << "\t[2] Player vs Computer " << endl;
		cout << "\t\t[0] Exit " << endl;
		//cout << "Action: ";
		//пока не будет введена цифра (координата)
		while (!(cin >> selection))
		{
			cin.clear();	
			while (cin.get() != '\n');
		}

		//**********ЦВЕТНАЯ РАССКРАСКА ПРИ ВЫБОРЕ**********
			//выбор 1
		if (selection == 1)
		{
			system("cls");			//очистка экрана 
			cout << "[Select game mode] " << endl << endl;
			MyColor(Yellow, Black);		//желтый цвет 
			cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
			cout << "[1] Player vs Player " << endl;
			cout << "\t[2] Player vs Computer " << endl;
			cout << "\t\t[0] Exit " << endl;
			Sleep(500);			//задерка 0.5 сек 
		}	
			//выбор 2
		else if (selection == 2)
		{
			system("cls");			//очистка экрана 
			cout << "[Select game mode] " << endl << endl;
			cout << "\t[1] Player vs Player " << endl;
			MyColor(Yellow, Black);			//желтый цвет 
			cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
			cout << "[2] Player vs Computer " << endl;
			cout << "\t\t[0] Exit " << endl;
			Sleep(500);
		}
			//выбор 0
		else if (selection == 0)
		{
			system("cls");			//очистка экрана 
			cout << "[Select game mode] " << endl << endl;
			cout << "\t[1] Player vs Player " << endl;
			cout << "\t[2] Player vs Computer " << endl;
			MyColor(Yellow, Black);			//желтый цвет
			cout << "\t\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
			cout << "[0] Exit " << endl;
			Sleep(500);				//задержка 0.5 сек
		}
		//менюшка
		switch (selection)
		{
		case 0:
		{
			system("cls");			//очистка экрана
			MyColor(LightRed, Black);		//светло - красный цвет
				cout << "\t\t\t\t\t\t  *-*-*[GOODBYE]*-*-*" << endl;
			Sleep(2000);			//задержка 2 сек 
			exit(1);			//выход из программы 
		}
		case 1:
		{
			system("cls");			//очистка экрана
			//для выбора расстановки
			int tmp_action;

			do
			{
				system("cls");				//очистка экрана 
				MyColor(LightCyan, Black);			//светло - бирюзовый 
				cout << "[Player vs Player] " << endl << endl;
				cout << "\t[1] Set ships rand, " << human1.name << endl;
				cout << "\t[2] Set ships manually, " << human1.name << endl;
				cout << "\t[3] Set ships rand, " << human2.name << endl;
				cout << "\t[4] Set ships manually, " << human2.name << endl;
				cout << "\t[5] Rename players " << endl;
				cout << "\t[6] Start BATTLE " << endl;
				cout << "\t\t[0] Back to main menu " << endl;
				//cout << "Action: ";
							//пока не будет введена цифра (координата)
				while (!(cin >> tmp_action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}

				//**********ЦВЕТНАЯ РАССКРАСКА ПРИ ВЫБОРЕ**********
					//выбор 1
				if (tmp_action == 1)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					MyColor(Yellow, Black);				//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек 
				}
					//выбор 2
				else if (tmp_action == 2)
				{
					system("cls");				//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					MyColor(Yellow, Black);				//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек 
				}
					//выьор 3
				else if (tmp_action == 3)
				{
					system("cls");			//очистка экрана
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					MyColor(Yellow, Black);			//желтый цвет
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек
				}
					//выбор 4
				else if (tmp_action == 4)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					MyColor(Yellow, Black);			//желтый цвет
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек
				}
					//выбор 5
				else if (tmp_action == 5)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					MyColor(Yellow, Black);			//желтый цвет
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек 
				}
					//выбор 6 
				else if (tmp_action == 6)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[6] Start BATTLE " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек 
				}

					//выбор 0 
				else if (tmp_action == 0)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Player] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Set ships rand, " << human2.name << endl;
					cout << "\t[4] Set ships manually, " << human2.name << endl;
					cout << "\t[5] Rename players " << endl;
					cout << "\t[6] Start BATTLE " << endl;
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "\t\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[0] Back to main menu " << endl;
					MyColor(LightCyan, Black);		//светло - бирюзовый цвет 
					Sleep(500);				//задержка 0.5 сек 
				}
				//менюшка
				switch (tmp_action)
				{
					case 1:
						{
							system("cls");			//очистка экрана 
								//если количество кораблей Игрок1 10, то возможность установки запрещается 
							if (human1.num_ship == 10){
								cout << "Ships have been installed, " << human1.name << endl;
								Sleep(1000);			//задержка 1 сек 
								break;
							}

							human1.all_set_ships_rand();			//метод установки кораблей
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//задержка 1 сек 
							break;
						}	//case 1
					case 2:
						{
							system("cls");			//очистка экрана 
								//если количество кораблей Игрок1 10, то возможность установки запрещается 
							if (human1.num_ship == 10){
								cout << "Ships have been installed, " << human1.name << endl;
								Sleep(1000);			//задержка 1 сек 
								break;
							}

							human1.all_set_ships_manually();		//метод установки кораблей
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//задержка 1 сек 
							break;
						}	//case 2
					case 3:
						{
							system("cls");			//очистка экрана 
								//если количество кораблей Игрок2 10, то возможность установки запрещается 
							if (human2.num_ship == 10){
								cout << "Ships have been installed, " << human2.name << endl;
								Sleep(1000);			//задержка1 сек 
								break;
							}

							human2.all_set_ships_rand();			//метод установки кораблей	
							cout << human2.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//задержка 1 сек 		
							break;
						}	//case 3
					case 4:
						{
							system("cls");			//очистка экрана 
								//если количество кораблей Игрок2 10, то возможность установки запрещается 
							if (human2.num_ship == 10){
								cout << "Ships have been installed, " << human2.name << endl;
								Sleep(1000);			//задержка 1 сек 
								break;
							}

							human2.all_set_ships_manually();		//метод установки кораблей	
							cout << human2.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//задержка 1 сек 
							break;
						}	//case 4
					case 5:
						{
							system("cls");			//очистка экрана 
								//ввод имени Игрок1
							cout << "Entered new name, " << human1.name << endl;
							cin >> human1;
								//ввод имени Игрок2
							cout << "Entered new name, " << human2.name << endl;
							cin >> human2;

							Sleep(1000);			//задержка 1 сек
							break;
						}
					case 6:
						{
							system("cls");			//очистка экрана 
							//Если количество кораблей Игрока1 меньше 10
							if (human1.num_ship < 10 && human2.num_ship == 10){
								cout << "Ships not installed, " << human1.name << endl;			//Корабли не установлены
								Sleep(1500);			//задержка 1.5 сек 
								break;
							}
							//если оба игрока не установили корабли
							else if (human1.num_ship < 10 && human2.num_ship < 10)
							{
								cout << "The players set their ships! " << endl;				//Игроки, установите свои корабли
								Sleep(1500);			//задержка 1.5 сек 
								break;
							}
							//Если количество кораблей Игрока2 меньше 10
							else if (human2.num_ship < 10 && human1.num_ship == 10){
								cout << "Ships not installed, " << human2.name << endl;			//Корабли не установлены
								Sleep(1500);			//задержка 1.5 сек
								break;	
							}
								
							//**********START GAME**********
							//определение "Кто первый ходит"
							int determination = rand() % 2 + 1;
							//если 1, то ход Игрок1
							if (determination == 1) {
								system("cls");			//очистка экрана
								cout << "The first goes, " << human1.name << endl << endl;
								Sleep(1500);			//задержка 1.5 сек
								//system("cls");
							}
							else {
								system("cls");			//очистка экрана
								cout << "The first goes, " << human2.name << endl << endl;
								Sleep(1500);		//задержка 1.5 сек 
								//system("cls");
							}

							//3..2..1..FIGHT! - Start battle 
							game.timer_start_battle();	//таймер до начала боя 

							//**********BATTLE**********
							if (determination == 1)
								game.Player_vs_Player(human1, human2);
							else
								game.Player_vs_Player(human2, human1);
							break;
						}
				}	//switch

			} while (tmp_action);

			break;

		}	//case 1
		case 2:
		{
			int action;		//выбор по менюшке
			do
			{
				system("cls");			//очистка экрана 
				MyColor(LightCyan, Black);			//светло - бирюзовый цвет 
				cout << "[Player vs Computer] " << endl << endl;
				cout << "\t[1] Set ships rand, " << human1.name << endl;
				cout << "\t[2] Set ships manually, " << human1.name << endl;
				cout << "\t[3] Rename players " << endl;
				cout << "\t[4] Start game " << endl;
				cout << "\t\t[0] Back to main menu " << endl;
				//cout << "Action: ";  
				//пока не будет введена цифра (координата)
				while (!(cin >> action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}
					//выбор 1
				if (action == 1)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Computer] " << endl << endl;
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задерка 0.5 сек 
				}
					//выбор 2
				else if (action == 2)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					MyColor(Yellow, Black);				//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[2] Set ships manually, " << human1.name << endl;	
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек
				}
					//выбор 3
				else if (action == 3)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);			//задержка 0.5 сек 
				}
					//выбор 4
				else if (action == 4)
				{
					system("cls");			//очистка экрана 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					MyColor(Yellow, Black);			//желтый цвет 
					cout << "\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[4] Start game " << endl;
					cout << "\t\t[0] Back to main menu " << endl;
					Sleep(500);		//задержка 0.5 сек
				}
					//выбор 0
				else if (action == 0)
				{
					system("cls");		//очистка экрана 
					cout << "[Player vs Computer] " << endl << endl;
					cout << "\t[1] Set ships rand, " << human1.name << endl;
					cout << "\t[2] Set ships manually, " << human1.name << endl;
					cout << "\t[3] Rename players " << endl;
					cout << "\t[4] Start game " << endl;
					MyColor(Yellow, Black);			//желтый цвет
					cout << "\t\t--> ";MyColor(LightCyan, Black);	//светло - бирюзовый цвет 
					cout << "[0] Back to main menu " << endl;
					Sleep(500);			//очистка экрана 
				}
				//менюшка
				switch (action)
				{
					case 1:
						{
							system("cls");		//очистка экрана 
								//если количество кораблей Игрок1 10, то возможность установки запрещается 
							if (human1.num_ship == 10){
								cout << "Ships have been installed " << endl;
								Sleep(1000);			//задержка 1 сек
								break;
							}

							human1.all_set_ships_rand();			//метод установки кораблей

							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);			//задержка 1 сек 
							break;
						}
					case 2:
						{
							system("cls");				//очистка экрана 
								//если количество кораблей Игрок1 10, то возможность установки запрещается
							if (human1.num_ship == 10){
								cout << "Ships have been installed " << endl;
								Sleep(1000);				//задержка 1 сек 
								break;
							}

							human1.all_set_ships_manually();			//метод установки кораблей
							cout << human1.name << ", ships succesfully installed " << endl;
							Sleep(1000);				//задержка 1 сек 
							break;
						}
					case 3:
						{
							system("cls");			//очистка экрана 
								//ввод нового имени Игрок1
							cout << "Entered new name, " << human1.name << endl;
							cin >> human1;	
								//ввод нового имени COMP
							cout << "Entered new name, " << comp.name << endl;
							cin >> comp;
							Sleep(1500);		//очистка экрана
							break;
						}
					case 4:
						{
							system("cls");			//очистка экрана 
							//если Игрок расстановил корабли, то устанавливаем Компу игроку
							if (human1.num_ship == 10)
								comp.all_set_ships_rand();		//метод установки кораблей 
								//если не установил, то выход в меню
							else{
								cout << human1.name << ", set their ships " <<endl;
								Sleep(1000);			//задержка 1 сек
								break;
							}
							//**********START GAME**********
							//определение "Кто первый ходит"
							int determination = rand() % 2 + 1;

							if (determination == 1) {
								system("cls");			//очистка экрана 
								cout << "The first goes, " << human1.name << endl << endl;
								Sleep(2000);			//задержка 2 сек 
								//system("cls");			
							}
							else {
								system("cls");				//очистка экрана
								cout << "The first goes, " << comp.name << endl << endl;
								Sleep(2000);				//задержка 2 сек 
								//system("cls");
							}

							//3..2..1..FIGHT! - Start battle (Начало боя)
							game.timer_start_battle();	//таймер до начала боя 

							//**********BATTLE**********
							if (determination == 1)
								game.Player_vs_COMP(human1, comp);
							else
								game.COMP_vs_Player(comp, human1);

							break;
						}
				}
			} while (action);
			break;
		}
		}
	} while (selection);
}
