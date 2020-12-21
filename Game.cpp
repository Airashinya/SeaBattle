#include "stdafx.h"

//******************������ ����******************
//����� ���� Player1 vs Player2
void Game::Player_vs_Player(Player player1OBJ, Player player2OBJ)
{
	system("cls");
	//����� �������� ���� ��� � ��������� �����
	player1OBJ.show_sea_battle_hidden_player();
	//����� ���� ��� ����
	cout << player2OBJ << endl;
	//���������� ��� ���
	MyColor(Magenta, LightBlue);
	cout << "����� ����� " << player1OBJ.name << endl;
	Sleep(2000);
	cout << "������� ���������� ������ A1 - J10: ";

	int row = 0;
	char column = ' ';

	//�������� �� ������� ��������
	if (player1OBJ.num_ship == 0)
	{
		system("cls");			//������� ������
		MyColor(LightRed, LightBlue);		//������� ����
		cout << player1OBJ.name << ", ��������. " << endl;	//� ��� �� �������� ��������, �� ���������
		MyColor(Black, LightBlue);			//������ - ��������� ����
		cout << endl << endl << "������� ����� ������� ��� �����������. " << endl;		//������ ����� ������� ��� �����������
		Sleep(4000);			//�������� 4 ���
		start_game();			//������ ����� ����
	}else if (player1OBJ.num_ship > 0)
	{
		//�������� �� ���� ���������
		do
		{
			//���� �� ����� ������ ������, ���� ����� �����������
			do
			{
				cin >> column;		//������ ����� (����������)
			}while(isdigit(column));
			//���� �� ����� ������� ����� (����������)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
			//�������� �������� �� ���� (tolower - ������ ������� ��������� �����)
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//�������������� ������ ������ ������� ��� �������� ����� -> �����
		int tmp = check_input_symb(column);	//������� ��������� ����� ��������� � ����� 

		row -= 1;	//�������� -1 ��� ��� ���������� ����� ������� � 0


		//���� ������� ����� �������� ����������
		if (player2OBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "� ���� ������ ��������� ����� ��� ��������� �������. " << endl;		//������� ��� ��� �������
			Sleep(1500);			//�������� 1.5 ���
			cout << "������, " << player1OBJ.name << endl;
			Player_vs_Player(player1OBJ, player2OBJ);			//��� �����1
			system("cls");			//������� ������
		}
		//���� ������� ����� ���� �������� ����
		else if (player2OBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "� ������ ������ ��� ��� ��������� �������. " << endl;	//�� ��� �������� � ��� �����
			Sleep(3000);				//�������� 1.5 ���
			cout << "������, " << player1OBJ.name << endl;
			system("cls");				//������� ������
			Player_vs_Player(player1OBJ, player2OBJ);			//��� �����1
		}
		//���� ������� ����� �����
		else if (player2OBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "������! " << endl;			//����� "����"
			player2OBJ.battle_field_arr[row][tmp] = bomb;			//������ ����� �� �������� ����
			player2OBJ.hiden_sea_battle[row][tmp] = bomb;			//������ ����� �� ������� ����
			Sleep(1500);				//�������� 1.5 ���
			cout << "������, " << player2OBJ.name << endl;			//
			system("cls");
			Player_vs_Player(player2OBJ, player1OBJ);			//��� �����2
		}
		//���� �� ������� ����� �������
		else if (player2OBJ.hiden_sea_battle[row][tmp] == ship)
		{
			player2OBJ.battle_field_arr[row][tmp] = hit;			//������ ����� ��������� �� �������� ����
			player2OBJ.hiden_sea_battle[row][tmp] = hit;			//������ ����� ��������� �� ������� ����

			//�������� ��� �������� ������� �� �������� ������
			vector<SHIP>::iterator _itShips = find_if(player2OBJ.ships.begin(), player2OBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//������� �������� �� ������� �� �������� ������ 
			if (_itShips != player2OBJ.ships.end())
			{
				_itShips->num_shot++;				//+1 � ���������� ���������
				//���� ���������� ��������� ��������� ���������� �����
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, LightBlue);		//������� ����
					cout << "������� ��������" << endl;			//����� "����"
					player2OBJ.num_ship--;		//-1 �� ���������� ������� ������
					_itShips->alive = false;	//������� ���� 
					_itShips->dead_zone_the_ship(player2OBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� ������� �� ������� ���� ���
					_itShips->dead_zone_the_ship(player2OBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� ������� �� �������� ���� ���
				}else
				{
					MyColor(Yellow, LightBlue);			//����� ����
					cout << "������� ����� " << endl;		//����� "�����"
				}
			}

			Sleep(5000);			//�������� 5 ���
			system("cls");			//������� ������
			//�������� ��� ���� ���
			Player_vs_Player(player1OBJ, player2OBJ);				//��� �����1
		}
	}
}
//����� ���� COMP vs Player (��� ���������)
void Game::COMP_vs_Player(Player compOBJ, Player playerOBJ)
{
	system("cls");
	compOBJ.show_sea_battle_hidden_player();		//����� �������� ���� ��� �����
	
		//���� ���������� �������� ������ 0, �� �� �������� 
		if (playerOBJ.num_ship == 0)
		{
			system("cls");					//������� ������
			playerOBJ.show_sea_battle_hidden_player();
			MyColor(LightRed, LightBlue);		//������ - ������� ����
			cout << playerOBJ.name << ", ��������!!! " << endl;	//� ��� �� �������� ��������, �� ���������
			MyColor(Black, LightBlue);		//������ - ���������
			Sleep(4000);			//�������� 4 ���
			start_game();			//����� ���� ������
		}
	
		//�������� �� ������� ��������
		else if (compOBJ.num_ship > 0)
		{
		//������������� ���������
			//���� true, �� ����������
			//���� false, �� �������� ������� ���������� ��� ����������� �������� �� ��������� �������
			if (new_generate_koordinat == true)
			{
				_x_ = rand() % 10;
				_y_ = rand() % 10;
				new_generate_koordinat = false;		//������ ����� ���������
			}

			//���� ������� ����� �������� ����������	(�������� �� ������������� ����)
			if (playerOBJ.battle_field_arr[_x_][_y_] == hit && alive_ship_on_which_the_last_hit == false)
			{
				system("cls");						//������� ������
				new_generate_koordinat = true;		//��������� ��������� ����� ���������
				COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
			}
			//���� ������� ����� ���� �������� ����	(�������� �� ������������� ����)
			else if (playerOBJ.battle_field_arr[_x_][_y_] == bomb)
			{
				system("cls");							//������� ������
				new_generate_koordinat = true;			//��������� ��������� ����� ���������
				COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
			}
			//���� ������� ����� �����	(�������� �� ������������� ����)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == tag_sea)
			{
				if (playerOBJ.hiden_sea_battle[_x_][_y_] != ship && 
					playerOBJ.hiden_sea_battle[_x_][_y_] != hit){
				playerOBJ.battle_field_arr[_x_][_y_] = bomb;		//��������� ����� �� ������� ������, �� �������� ���� ���
				playerOBJ.hiden_sea_battle[_x_][_y_] = bomb;		//��������� ����� �� ������� ������, �� ������� ���� ���
				}
				cout << "������! " << endl;
				Sleep(1500);
				system("cls");								//������� ������
				new_generate_koordinat = true;				//��������� ��������� ����� ���������
				Player_vs_COMP(playerOBJ, compOBJ);			//��� �����
			}
			//���� �� ������� ����� �������	(�������� �� ������� ����)
			else if (playerOBJ.hiden_sea_battle[_x_][_y_] == ship || alive_ship_on_which_the_last_hit == true)
			{
				playerOBJ.battle_field_arr[_x_][_y_] = hit;		//��������� ����� ��������� ��� ��������� �� �������� ���� ���
				playerOBJ.hiden_sea_battle[_x_][_y_] = hit;		//��������� ����� ��������� ��� ��������� �� ������� ���� ���
				system("cls");			//������� ������
				playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
				MyColor(Yellow, LightBlue);			//������ ����
				cout << "������� ������ " << endl;		//����� �� ����� "�����"
				Sleep(3000);			//�������� 5 ���	

				//�������� ��� �������� ������� �� �������� ������
				vector<SHIP>::iterator _itShips = find_if(playerOBJ.ships.begin(), playerOBJ.ships.end(), PREDICAT_downed_ship(_x_, _y_));
				//������� ��������
				if (_itShips != playerOBJ.ships.end())
				{
					if (alive_ship_on_which_the_last_hit == false)
						_itShips->num_shot++;			//+1 � ����������
					//���� ��������� ���� �� ��������� ������, �� ������� ���� � ��������� � ����� ��������� ���������
					if (_itShips->num_deck_ship == _itShips->num_shot)
					{
						MyColor(LightRed, LightBlue);			//������ - ������� ����
						cout << "������� �������� " << endl;			//����� �� ����� ��� �������� "����"
						_itShips->alive = false;			//�������� � ������� ������� ������� ����
						new_generate_koordinat = true;		//��������� ��������� ����� ���������
						alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
						playerOBJ.num_ship--;				//-1 ������� �� ���� �������� ������, ��� ��������
						_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, VERTICAL);				//��������� ������� ���� ��� �������� (�� �������� ����)
						_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, VERTICAL);				//��������� ������� ���� ��� �������� (�� ������� ����)
						Sleep(3000);					//�������� 5 ���
						COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
					}	
					//******************************************************************************************************
					
						//���������, ����� ������ �������� ��� ������ �����/������
						int tmp_column = _y_;		//���������� �������

						//------------->	�������� ������ �� ����������� 
						if (_itShips->alive == true && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship  && _y_ + 1 <= COLUMNS - 1)
						{
						
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == ship)
							{
								_itShips->num_shot++;		//+1 � �����������
								playerOBJ.battle_field_arr[_x_][tmp_column + 1] = hit;			//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = hit;			//�� ������� ���� ������ ����� ���������
								system("cls");				//������� ������
								playerOBJ.show_sea_battle_hidden_player();		//����� �������� ���� ���
								MyColor(Yellow, LightBlue);					//������ ����
								cout << "������� ������ " << endl;				//����� "�����"
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(2000);			//�������� 3 ���
								tmp_column += 1;		//����� ������ �� 1 ������
							}
								//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, LightBlue);			//������� ����
									cout << "������� ��������" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� �������� ������
									_itShips->alive = false;			//������� ����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);		//��������� ������� ���� �� �������� ���� ��� 
									Sleep(2000);				//�������� 3 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								}
							//���� ������� ��������� � ������ ���� � ���
							if (_itShips->y_end == COLUMNS - 1 && _itShips->alive == true)
							{
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
								//���� ������� ��������� � ������ ���� � ����
							else if (_itShips->y_end == COLUMNS - 1  && _itShips->alive == false)
							{
								new_generate_koordinat = true;			//��������� ������������ ����� ���������� ��� ��������
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
								//���� ������� �� ��������� � ������ ���� � ���
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column + 1] = bomb;			//�� �������� ���� ��� ������ �����
									playerOBJ.hiden_sea_battle[_x_][tmp_column + 1] = bomb;			//�� ������� ���� ��� ������ �����
								}
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Player_vs_COMP(playerOBJ, compOBJ);		//��� ������
							}		
								//���� ������� �� ��������� � ������ ���� � ����
							else if (_itShips->y_end + 1 <= COLUMNS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;			//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);		//��� �����
							}
						}
						//******************************************************************************************************
						//<-------------	�������� ����� �� ����������� 
						if (_itShips->alive == true && new_generate_koordinat == false && _itShips->dir_n == HORIZONTAL &&
							playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship  && _y_ - 1 >= 0)
						{
						
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == ship)
							{
								_itShips->num_shot++;				//+1 � ���������� ��������� �� �������
								playerOBJ.battle_field_arr[_x_][tmp_column - 1] = hit;			//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = hit;			//�� ������� ���� ������ ����� ���������
								system("cls");					//������� ������
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								MyColor(Yellow, LightBlue);			//������ ����
								cout << "������� ������ " << endl;			//����� "�����"
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(2000);			//�������� 3 ���
								tmp_column -= 1;			//����� �����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, LightBlue);				//������� ����
									cout << "������� ��������" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� �������� 
									_itShips->alive = false;			//��������, ��� ������� ����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� �������� ���� ��� 
									Sleep(2000);				//�������� 3 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();				//����� �������� ���� ��� 
								}
							//���� ������� ��������� � ����� ���� � ���
							if (_itShips->y_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� ��������� � ����� ���� � ����
							else if (_itShips->y_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;					//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� �� ��������� � ����� ���� � ���
							else if (_itShips->y_begin - 1 > 0  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;								//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] == tag_sea)
								{
									playerOBJ.battle_field_arr[_x_][tmp_column - 1] = bomb;		//�� - 1 ������ ������ ����� (�� �������� ����)
									playerOBJ.hiden_sea_battle[_x_][tmp_column - 1] = bomb;		//�� - 1 ������ ������ ����� (�� ������� ����)
								}
								Player_vs_COMP(playerOBJ, compOBJ);							//��� ������
							}
								//���� ������� �� ��������� � ����� ���� � ����
							else if (_itShips->y_begin - 1 >= 0  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;							//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);						//��� �����
							}
						}
			//******************************************************************************************************
						//���������, ����� ������� �������� ��� ������ �����/����
						int tmp_row = _x_;			//��������� ���������� ������
					
						// |
						// |
						// |
						// |
						// |
						//\_/
						//�������� ���� �� ���������
						if (_itShips->alive == true && _itShips->dir_n == VERTICAL &&
							playerOBJ.hiden_sea_battle[_x_ + 1][_y_] == ship && _x_ + 1 <= ROWS - 1)
						{
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 � ��������� ��������� �� �������
								playerOBJ.battle_field_arr[tmp_row + 1][_y_] = hit;			//�������� ������ ���������
								playerOBJ.hiden_sea_battle[tmp_row + 1][_y_] = hit;
								system("cls");
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								MyColor(Yellow, LightBlue);
								cout << "������� ������ " << endl;	
								new_generate_koordinat = false;			//������ ����� ��������� ���������
								Sleep(2000);
								tmp_row += 1;			//����� ����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, LightBlue);
									cout << "������� ��������" << endl;
									playerOBJ.num_ship--;				//-1 �� ���������� �������� 
									_itShips->alive = false;			//������� �����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);				//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);				//��������� ������� ���� �� �������� ���� ��� 
									Sleep(2000);
									system("cls");
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ���
								}
								//���� ������� ��������� ���� � ���
							if (_itShips->x_end == ROWS - 1 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� ��������� ���� � ����
							else if (_itShips->x_end == ROWS - 1 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;					//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);				//��� �����
							}
								//���� ������� �� ��������� ���� � ���
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;					//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row + 1][tmp_column] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row + 1][tmp_column] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);		//��� ������
							}
								//���� ������� �� ��������� ���� � ����
							else if (_itShips->x_end + 1 <= ROWS - 1  && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
						}
			//******************************************************************************************************
						//�������� ����� �� ���������
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
							//���� +1 ������ �������
							while (playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] == ship)
							{
								_itShips->num_shot++;				//+1 � ���������� ��������� �� ������� 
								playerOBJ.battle_field_arr[tmp_row - 1][_y_] = hit;		//�� �������� ���� ������ ����� ���������
								playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = hit;		//�� ������� ���� ������ ����� ���������
								system("cls");				//������� ������
								playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								MyColor(Yellow, LightBlue);				//������ ����
								cout << "������� ������ " << endl;			//����� "�����"
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								Sleep(2000);			//�������� 3 ���
								tmp_row -= 1;				//����� �����
							}
							//���� ���������� ��������� �� ������� ��������� ���������� ����� 
								if (_itShips->num_shot == _itShips->num_deck_ship)
								{
									MyColor(LightRed, LightBlue);			//������ - ������� ����
									cout << "������� ��������" << endl;				//����� "����"
									playerOBJ.num_ship--;				//-1 �� ���������� ��������
									_itShips->alive = false;			//������� �����
									new_generate_koordinat = true;		//��������� ������������ ����� ���������� ��� ��������
									_itShips->dead_zone_the_ship(playerOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);					//��������� ������� ���� �� ������� ���� ��� 
									_itShips->dead_zone_the_ship(playerOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);					//��������� ������� ���� �� �������� ���� ��� 
									Sleep(2000);				//�������� 3 ���
									system("cls");				//������� ������
									playerOBJ.show_sea_battle_hidden_player();			//����� �������� ���� ��� 
								}
								//���� ������� ��������� ����� � ���
							if (_itShips->x_begin == 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}	
								//���� ������� ��������� ����� � ����
							else if (_itShips->x_begin == 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
								//���� ������� �� ��������� ����� � ���
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == true)
							{
								alive_ship_on_which_the_last_hit = true;			//�������, ��� ������� �� �������� ��� ������� ���
								new_generate_koordinat = false;				//������ ����� ��������� ���������
								if (playerOBJ.hiden_sea_battle[_x_ - 1][tmp_column] == tag_sea)
								{
									playerOBJ.battle_field_arr[tmp_row - 1][_y_] = bomb;
									playerOBJ.hiden_sea_battle[tmp_row - 1][_y_] = bomb;
								}
								Player_vs_COMP(playerOBJ, compOBJ);			//��� ������
							}
								//���� ������� �� ��������� ����� � ����
							else if (_itShips->x_begin - 1 >= 0 && _itShips->alive == false)
							{
								alive_ship_on_which_the_last_hit = false;			//�������, ��� ������� �� �������� ��� ������� �����
								new_generate_koordinat = true;				//��������� ������������ ����� ���������� ��� ��������
								COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
							}
						}
				}
				COMP_vs_Player(compOBJ, playerOBJ);			//��� �����
			}
	}
}
//����� ���� Player vs COMP	(��� �����)
void Game::Player_vs_COMP(Player player1OBJ, Player compOBJ)
{
	system("cls");
	//����� �������� ���� ��� � ��������� �����
	player1OBJ.show_sea_battle_hidden_player();
	//����� ���� ��� ����
	cout << compOBJ << endl;
	MyColor(Magenta, LightBlue);

	cout << "�����  " << player1OBJ.name << endl;
	cout << "������� ���������� ������ ��� ����  A1 - J10: ";

	int row = 0;
	char column = ' ';

	//�������� �� ������� ��������

	//���� ���������� �������� ����� 0, �� �� ��������
	if (compOBJ.num_ship == 0)
	{
		system("cls");				//������� ������
		MyColor(LightRed, LightBlue);			//������� ����
		cout << compOBJ.name << ", ��������!!! " << endl;	//� ��� �� �������� ��������, �� ���������
		MyColor(Black, LightBlue);			//������ - ���������
		Sleep(4000);				//�������� 4 ���
		start_game();				//����� ����� ����
	}
	//���� ���������� �������� ������ 0, ������������ ����
	if (player1OBJ.num_ship > 0)
	{
		//�������� �� ���� ���������
		do
		{
			//���� �� ����� ������ ������, ���� ����� �����������
			do
			{
				cin >> column;		//����� ����� (����������)
			}while(isdigit(column));
			//���� �� ����� ������� ����� (����������)
			while (!(cin >> row))
			{
				cin.clear();	
				while (cin.get() != '\n');
			}
		} while ((tolower(column) < 'a' && tolower(column) > 'j') && (row >= 1 || row <= 10));

		//�������������� ������ ������ ������� ��� �������� ����� -> �����
		int tmp = check_input_symb(column);	//������� ��������� ����� ��������� � ����� 

		row -= 1;	//�������� -1 ��� ��� ���������� ����� ������� � 0


		//���� ������� ����� �������� ����������
		if (compOBJ.battle_field_arr[row][tmp] == hit)
		{
			cout << "� ���� ������ ��������� ����� ��� ��������� ������� " << endl;	//������� ��� ��� �������
		Sleep(1500);		//�������� 1.5 ���
			cout << "������, " << player1OBJ.name << endl;
			Player_vs_COMP(player1OBJ, compOBJ);			//��� ������
			system("cls");				//������� ������
		}
		//���� ������� ����� ���� �������� ����
		else if (compOBJ.battle_field_arr[row][tmp] == bomb)
		{
			cout << "� ������ ������ ��� ��� ��������� �������. " << endl;	//�� ��� �������� � ��� �����
			Sleep(1500);			//�������� 1.5 ���
			cout << " ������, " << player1OBJ.name << endl;
			system("cls");			//������� ������
			Player_vs_COMP(player1OBJ, compOBJ);				//��� ������
		}
		//���� ������� ����� �����
		else if (compOBJ.hiden_sea_battle[row][tmp] == tag_sea)
		{
			cout << "������! " << endl;				//����� "����"
			if (compOBJ.battle_field_arr[row][tmp] != ship){
			compOBJ.battle_field_arr[row][tmp] = bomb;			//������ ����� �� �������� ����
			compOBJ.hiden_sea_battle[row][tmp] = bomb;			//������ ����� �� �������� ����
			}
			Sleep(1500);			//�������� 1.5 ���
			cout << "������, " << compOBJ.name << endl;
			system("cls");			//������� ������
			COMP_vs_Player(compOBJ, player1OBJ);				//��� �����
		}
		//���� �� ������� ����� �������
		else if (compOBJ.hiden_sea_battle[row][tmp] == ship)
		{
			compOBJ.battle_field_arr[row][tmp] = hit;		//������ ����� ��������� �� �������� ���� 
			compOBJ.hiden_sea_battle[row][tmp] = hit;		//������ ����� ��������� �� �������� ���� 

			//�������� ��� �������� ������� �� �������� ������
			vector<SHIP>::iterator _itShips = find_if(compOBJ.ships.begin(), compOBJ.ships.end(), PREDICAT_downed_ship(row, tmp));
			
			//������� �������� �� ������ �� �������� ������ 
			if (_itShips != compOBJ.ships.end())
			{
				_itShips->num_shot++;			//+1 � ���������� ���������
				//���� ���������� ��������� �� ������� ��������� ���������� ����� 
				if (_itShips->num_shot == _itShips->num_deck_ship)
				{
					MyColor(LightRed, LightBlue);		//������� ����
					cout << "������� ��������" << endl;			//����� "����"
					compOBJ.num_ship--;			//-1 �� ���������� �������� �����
					_itShips->alive = false;	//�������� �����
					_itShips->dead_zone_the_ship(compOBJ.hiden_sea_battle,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� ������� ���� ���
					_itShips->dead_zone_the_ship(compOBJ.battle_field_arr,_itShips->alive, _itShips->dir_n);			//��������� ������� ���� �� �������� ���� ���
				}else
				{
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "������� ������ " << endl;		//����� "�����"
				}
			}

			Sleep(2000);			//�������� 3 ��� 
			system("cls");			//������� ������
			//�������� ��� ���� ���
			Player_vs_COMP(player1OBJ, compOBJ);			//��� ������
		}
	}
}
//������ ������ ���
void Game::timer_start_battle()
{
		system("cls");
		MyColor(LightRed, LightBlue);
		for (int i = 3; i >= 1; i--)
		{
			cout << "\t\t\t\t\t\t\t" << i;	
			Sleep(1000);
			system("cls");
		}
		cout << "\t\t\t\t\t\t  ���� ��������, � ���! " << endl;
		Sleep(1000);
		system("cls");

	}
//����������� � ����
void Game::designations_in_game()
	{
		//����������� � ����
		cout << "����� ���������� � ���� '������� ���!'"<< endl<< endl;
		cout << "����� ������� ������������ � ������������� � ����" << endl << endl;
		cout << "\t������� ������ ����: ";
		MyColor(DarkGray, LightBlue);
		cout << bomb << endl;				//�����
		MyColor(Black, LightBlue);
		cout << "\t������� ����� �� ������� : ";
		MyColor(LightRed, LightBlue);
		cout << hit << endl;				//��������� �� �������
		MyColor(Black, LightBlue);
		cout << "\t����� �������: ";
		MyColor(Green, LightBlue);
		cout << ship << endl;				//�������
		MyColor(Black, LightBlue);
		cout << endl << endl << "������� ����� ������� ��� �����������. " << endl;		
		_getch();			//��� ������� �������
		system("cls");
		cout << "������� ���� " << endl << endl
			<< "������� ��� - ���� ���������� �� ���� 10�10 �������� ������� ������, �� ������� ����������� ���� ��������. ���� ������� ��:"
			<< "1 ������� - ��� �� 4 ������/ �������������� /�������"
			<< "2 ������� - ��� �� 3 ������/ �����������/ ������� "
			<< "3 ������� - ��� �� 2 ������* ������������/�������"
			<< "4 ������� - 1 ��������/ ������������/ ������"
			<< "��� ���������� ������� �� ����� �������� ���� ����� ������. ������ �������� ���� ������� �� �������, � �� ��������."<<endl
			<<" �������: ������ ������� ������ ������ ������� �� ���������. ����� ������� ������ �������� ��������� ������� ������������ ������ �������." << endl
			<< " �����, ����������� ���, ��������� ������� � ����� ���������� ������, � �������, �� ��� ������, ��������� ������� ����������, ��������, �A1�. " << endl 
			<< "���� ������� �������� � ������, �� ������� �� ����� ������� ����������, �� ������� ����� �����!� � ���������� ����� ������ �� ����� �������� � ���� ����� �����. ����� ���� ��������� � ���������." << endl 
			<< " ���� ������� �������� � ������, ��� ��������� ������������� ������� (�������� ������ ��� 1 ������), �� ������� ����� ������!�. " << endl
			<< "���������� ����� ������ �� ����� ���� � ��� ������ �������, � ��� ��������� ������ ������� �� ���� ���� ����� � ��� ������. ���������� ����� �������� ����� �� ��� ���� �������." << endl 
			<< " ���� ������� �������� � ������, ��� ��������� ������������ ������� ��� ��������� ����������� ������ �������������� �������, �� ������� ����� ���������!� ��� �����!�. ��� ������ �������� ����������� ������� �� �����." << endl 
			<< "��� �� ���� ��������� � 1 �������� ������ ������������ ������� ��������� ������� �����, ���� �������� ����� �� ����� ������ � ��� �� ���������� �������.  ���������� ����� �������� ����� �� ��� ���� �������." << endl 
			<< " ����������� ��������� ���, ��� ������ ������� ��� 10 �������� ����������."
			<< endl << "������ ������� ����!";
		cout << endl << endl << "������� ����� ������� ��� �����������. " << endl;
		_getch();			//��� ������� �������
		system("cls");
}
//������ ����
void Game::start_game()
{
	system("cls");			//������� ������ 
	//**********����������**********
	Player human1("�����1");			//��������� ��� �����1
	Player human2("�����2");			//��������� ��� �����2
	SHIP obj_ship;						//��������� ������ �������
	Player comp("���������");				//��������� ��� COMP
	Game game;							//��������� ������ ����

	MyColor(Black, LightBlue);			//������ - ���������
	game.designations_in_game();		//����� ����������� � ����
	

	int selection = 0;	//����� �� �������	

	do
	{
		system("cls");				//������� ������ 
		MyColor(Black, LightBlue);	//������ - ��������� ����
		cout << "[�������� ����� ����] " << endl << endl;
		cout << "\t[1] ����� vs ������ " << endl;
		cout << "\t[2] ����� vs ��������� " << endl;
		cout << "\t\t[0] ����� " << endl;
		//cout << "Action: ";
		//���� �� ����� ������� ����� (����������)
		while (!(cin >> selection))
		{
			cin.clear();	
			while (cin.get() != '\n');
		}

		//**********������� ���������� ��� ������**********
			//����� 1
		if (selection == 1)
		{
			system("cls");			//������� ������ 
			cout << "[�������� ����� ����] " << endl << endl;
			MyColor(Yellow, LightBlue);		//������ ���� 
			cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
			cout << "[1] ����� ������ ������ " << endl;
			cout << "\t[2] ����� ������ ���������� " << endl;
			cout << "\t\t[0] ����� " << endl;
			Sleep(500);			//������� 0.5 ��� 
		}	
			//����� 2����� ������ ����������
		else if (selection == 2)
		{
			system("cls");			//������� ������ 
			cout << "[�������� ����� ����] " << endl << endl;
			cout << "\t[1] ����� ������ ������ " << endl;
			MyColor(Yellow, LightBlue);			//������ ���� 
			cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
			cout << "[2] ����� ������ ���������� " << endl;
			cout << "\t\t[0] ����� " << endl;
			Sleep(500);
		}
			//����� 0
		else if (selection == 0)
		{
			system("cls");			//������� ������ 
			cout << "[�������� ����� ����] " << endl << endl;
			cout << "\t[1] ����� ������ ������ " << endl;
			cout << "\t[2] ����� ������ ���������� " << endl;
			MyColor(Yellow, LightBlue);			//������ ����
			cout << "\t\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
			cout << "[0] ����� " << endl;
			Sleep(500);				//�������� 0.5 ���
		}
		//�������
		switch (selection)
		{
		case 0:
		{
			system("cls");			//������� ������
			MyColor(LightRed, LightBlue);		//������ - ������� ����
				cout << "\t\t\t\t\t\t  *-*-*[�� �������]*-*-*" << endl;
			Sleep(2000);			//�������� 2 ��� 
			exit(1);			//����� �� ��������� 
		}
		case 1:
		{
			system("cls");			//������� ������
			//��� ������ �����������
			int tmp_action;

			do
			{
				system("cls");				//������� ������ 
				MyColor(Black, LightBlue);			//������ - ��������� 
				cout << "[����� ������ ������] " << endl << endl;
				cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
				cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
				cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
				cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
				cout << "\t[5] ������������� ������� " << endl;
				cout << "\t[6] ������ ����! " << endl;
				cout << "\t\t[0] ����� � ���� " << endl;
				//cout << "Action: ";
							//���� �� ����� ������� ����� (����������)
				while (!(cin >> tmp_action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}

				//**********������� ���������� ��� ������**********
					//����� 1
				if (tmp_action == 1)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					MyColor(Yellow, LightBlue);				//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 2
				else if (tmp_action == 2)
				{
					system("cls");				//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					MyColor(Yellow, LightBlue);				//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 3
				else if (tmp_action == 3)
				{
					system("cls");			//������� ������
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					MyColor(Yellow, LightBlue);			//������ ����
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 4
				else if (tmp_action == 4)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					MyColor(Yellow, LightBlue);			//������ ����
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 5
				else if (tmp_action == 5)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					MyColor(Yellow, LightBlue);			//������ ����
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 6 
				else if (tmp_action == 6)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[6] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}

					//����� 0 
				else if (tmp_action == 0)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ���������� ������� �������� �������, " << human2.name << endl;
					cout << "\t[4] ���������� ������� �������, " << human2.name << endl;
					cout << "\t[5] ������������� ������� " << endl;
					cout << "\t[6] ������ ����! " << endl;
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "\t\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[0] ����� � ���� " << endl;
					MyColor(Black, LightBlue);		//������ - ��������� ���� 
					Sleep(500);				//�������� 0.5 ��� 
				}
				//�������
				switch (tmp_action)
				{
					case 1:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "������� �����������, " << human1.name << endl;
								Sleep(5000);			//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_rand();			//����� ��������� ��������
							cout << human1.name << ", ������� ������� ����������� " << endl;
							Sleep(5000);			//�������� 1 ��� 
							break;
						}	//case 1
					case 2:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "������� �����������, " << human1.name << endl;
								Sleep(5000);			//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_manually();		//����� ��������� ��������
							cout << human1.name << ", ������� ������� ����������� " << endl;
							Sleep(5000);			//�������� 1 ��� 
							break;
						}	//case 2
					case 3:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����2 10, �� ����������� ��������� ����������� 
							if (human2.num_ship == 10){
								cout << "������� �����������, " << human2.name << endl;
								Sleep(5000);			//��������1 ��� 
								break;
							}

							human2.all_set_ships_rand();			//����� ��������� ��������	
							cout << human2.name << ", ������� ������� ����������� " << endl;
							Sleep(5000);			//�������� 1 ��� 		
							break;
						}	//case 3
					case 4:
						{
							system("cls");			//������� ������ 
								//���� ���������� �������� �����2 10, �� ����������� ��������� ����������� 
							if (human2.num_ship == 10){
								cout << "������� �����������, " << human2.name << endl;
								Sleep(5000);			//�������� 1 ��� 
								break;
							}

							human2.all_set_ships_manually();		//����� ��������� ��������	
							cout << human2.name << ", ������� ������� ����������� " << endl;
							Sleep(5000);			//�������� 1 ��� 
							break;
						}	//case 4������� ������� �����������
					case 5:
						{
							system("cls");			//������� ������ 
								//���� ����� �����1
							cout << "������� ����� ���, " << human1.name << endl;
							cin >> human1;
								//���� ����� �����2
							cout << "������� ����� ���, " << human2.name << endl;
							cin >> human2;

							Sleep(1000);			//�������� 1 ���
							break;
						}
					case 6:
						{
							system("cls");			//������� ������ 
							//���� ���������� �������� ������1 ������ 10
							if (human1.num_ship < 10 && human2.num_ship == 10){
								cout << "������� �����������, " << human1.name << endl;			//������� �� �����������
								Sleep(1500);			//�������� 1.5 ��� 
								break;
							}
							//���� ��� ������ �� ���������� �������
							else if (human1.num_ship < 10 && human2.num_ship < 10)
							{
								cout << "������, ���������� �������! " << endl;				//������, ���������� ���� �������
								Sleep(1500);			//�������� 1.5 ��� 
								break;
							}
							//���� ���������� �������� ������2 ������ 10
							else if (human2.num_ship < 10 && human1.num_ship == 10){
								cout << "������� �� �����������, " << human2.name << endl;			//������� �� �����������
								Sleep(1500);			//�������� 1.5 ���
								break;	
							}
								
							//**********������ ����!**********
							//����������� "��� ������ �����"
							int determination = rand() % 2 + 1;
							//���� 1, �� ��� �����1
							if (determination == 1) {
								system("cls");			//������� ������
								cout << "������ ����� " << human1.name << endl << endl;
								Sleep(1500);			//�������� 1.5 ���
								//system("cls");
							}
							else {
								system("cls");			//������� ������
								cout << "������ ����� " << human2.name << endl << endl;
								Sleep(1500);		//�������� 1.5 ��� 
								//system("cls");
							}

							//3..2..1..FIGHT! - ������ ����! 
							game.timer_start_battle();	//������ �� ������ ��� 

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
			int action;		//����� �� �������
			do
			{
				system("cls");			//������� ������ 
				MyColor(Black, LightBlue);			//������ - ��������� ���� 
				cout << "[����� ������ ����������] " << endl << endl;
				cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
				cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
				cout << "\t[3] ������������� ������� " << endl;
				cout << "\t[4] ������ ����! " << endl;
				cout << "\t\t[0] ����� � ���� " << endl;
				//cout << "Action: ";  
				//���� �� ����� ������� ����� (����������)
				while (!(cin >> action))
				{
					cin.clear();	
					while (cin.get() != '\n');
				}
					//����� 1
				if (action == 1)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ����������] " << endl << endl;
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ������������� ������� " << endl;
					cout << "\t[4] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//������� 0.5 ��� 
				}
					//����� 2
				else if (action == 2)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ����������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					MyColor(Yellow, LightBlue);				//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[2] ���������� ������� �������, " << human1.name << endl;	
					cout << "\t[3] ������������� ������� " << endl;
					cout << "\t[4] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ���
				}
					//����� 3
				else if (action == 3)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ����������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[3] ������������� ������� " << endl;
					cout << "\t[4] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);			//�������� 0.5 ��� 
				}
					//����� 4
				else if (action == 4)
				{
					system("cls");			//������� ������ 
					cout << "[����� ������ ����������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ������������� ������� " << endl;
					MyColor(Yellow, LightBlue);			//������ ���� 
					cout << "\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[4] ������ ����! " << endl;
					cout << "\t\t[0] ����� � ���� " << endl;
					Sleep(500);		//�������� 0.5 ���
				}
					//����� 0
				else if (action == 0)
				{
					system("cls");		//������� ������ 
					cout << "[����� ������ ����������] " << endl << endl;
					cout << "\t[1] ���������� ������� �������� �������, " << human1.name << endl;
					cout << "\t[2] ���������� ������� �������, " << human1.name << endl;
					cout << "\t[3] ������������� ������� " << endl;
					cout << "\t[4] ������ ����! " << endl;
					MyColor(Yellow, LightBlue);			//������ ����
					cout << "\t\t--> ";MyColor(Black, LightBlue);	//������ - ��������� ���� 
					cout << "[0] ����� � ���� " << endl;
					Sleep(500);			//������� ������ 
				}
				//�������
				switch (action)
				{
					case 1:
						{
							system("cls");		//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� ����������� 
							if (human1.num_ship == 10){
								cout << "������� ����������� " << endl;
								Sleep(1000);			//�������� 1 ���
								break;
							}

							human1.all_set_ships_rand();			//����� ��������� ��������

							cout << human1.name << ", ������� ������� ����������� " << endl;
							Sleep(1000);			//�������� 1 ��� 
							break;
						}
					case 2:
						{
							system("cls");				//������� ������ 
								//���� ���������� �������� �����1 10, �� ����������� ��������� �����������
							if (human1.num_ship == 10){
								cout << "������� ����������� " << endl;
								Sleep(1000);				//�������� 1 ��� 
								break;
							}

							human1.all_set_ships_manually();			//����� ��������� ��������
							cout << human1.name << ", ������� ������� ����������� " << endl;
							Sleep(1000);				//�������� 1 ��� 
							break;
						}
					case 3:
						{
							system("cls");			//������� ������ 
								//���� ������ ����� �����1
							cout << "������� ����� ���, " << human1.name << endl;
							cin >> human1;	
								//���� ������ ����� COMP
							cout << "������� ����� ���, " << comp.name << endl;
							cin >> comp;
							Sleep(1500);		//������� ������
							break;
						}
					case 4:
						{
							system("cls");			//������� ������ 
							//���� ����� ����������� �������, �� ������������� ����� ������
							if (human1.num_ship == 10)
								comp.all_set_ships_rand();		//����� ��������� �������� 
								//���� �� ���������, �� ����� � ����
							else{
								cout << human1.name << " �� ��������� ������� " <<endl;
								Sleep(1000);			//�������� 1 ���
								break;
							}
							//**********������ ����!**********
							//����������� "��� ������ �����"
							int determination = rand() % 2 + 1;

							if (determination == 1) {
								system("cls");			//������� ������ 
								cout << "������ ����� " << human1.name << endl << endl;
								Sleep(2000);			//�������� 2 ��� 
								//system("cls");			
							}
							else {
								system("cls");				//������� ������
								cout << "������ ����� " << comp.name << endl << endl;
								Sleep(2000);				//�������� 2 ��� 
								//system("cls");
							}

							//3..2..1..FIGHT! - ������ ����! (������ ���)
							game.timer_start_battle();	//������ �� ������ ��� 

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
