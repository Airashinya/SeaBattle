#include "stdafx.h"

//обозначение мертвой зоны корабля
void SHIP::dead_zone_the_ship(char arr[][COLUMNS], bool _is_dead, direction dir_n)
{
	if (!_is_dead)
	{
		//VERTICAL
		if (dir_n == VERTICAL)
		{
			//если корабль в левом верхнем углу
			if (x_begin == 0 && y_begin == 0)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
				//under(под)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//если корабль у левого края
			else if (y_begin == 0 && x_begin - 1 >= 0)
			{
				//above(над)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
				//under(под)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//если корабль в левом нижнем углу
			else if (x_end == ROWS - 1 && x_begin + 1 >= ROWS - 1 && x_begin - 1 < 0)
			{
				//above(над)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
				}
			}
			//если корабль у верхнего края поля
			else if (x_begin == 0 && y_begin - 1 >= 0 && y_begin + 1 <= COLUMNS - 1)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin + 1] = bomb;
					arr[i][y_begin - 1] = bomb;
				}
				//under(под)
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
			//если корабль у нижнего края поля
			else if (x_end == ROWS - 1 && y_end - 1 >= 0 && y_end + 1 <= COLUMNS - 1)
			{
				//above(над)
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
					arr[i][y_begin + 1] = bomb;
				}
			}
			//если корабль в правом верхнем углу
			else if (x_begin == 0 && y_begin == COLUMNS - 1)
			{
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
			}
			//если корабль у правого края
			else if (y_begin == COLUMNS - 1 && x_begin - 1 >= 0 && x_end + 1 <= ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
			}
			//если корабль в правом нижнем углу
			else if (y_end == COLUMNS - 1 && x_end == ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
				}
			}
			//если корабль не касается краёв поля
			else if (y_begin - 1 >= 0 && y_begin + 1 <= COLUMNS - 1 && x_begin - 1 >= 0 && x_end + 1 <= ROWS - 1)
			{
				//above
				arr[x_begin - 1][y_begin] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin + 1] = bomb;
				for (int i = x_begin; i < x_begin + num_deck_ship; i++)
				{
					arr[i][y_begin - 1] = bomb;
					arr[i][y_begin + 1] = bomb;
				}
				//under
				arr[x_end + 1][y_begin] = bomb;
				arr[x_end + 1][y_begin - 1] = bomb;
				arr[x_end + 1][y_begin + 1] = bomb;
			}
		}
		//HORIZONTAL
		else if (dir_n == HORIZONTAL)
		{
			//правый верхний угол
			if (y_end == COLUMNS - 1 && x_end == 0)
			{
				//after
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
			}
			//корабль, который не касается краёв поля
			else if (x_begin - 1 >= 0 && y_begin - 1 >= 0 && x_end + 1 <= ROWS - 1 && y_end + 1 <= COLUMNS - 1)
			{
				//before(перед)
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
					arr[x_begin + 1][i] = bomb;
				}
				//after(после)
				arr[x_end - 1][y_end + 1] = bomb;
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;

			}
			//корабль, который упирается в правый край
			else if (x_begin - 1 >= 0 && x_begin + 1 <= ROWS - 1 && y_end == COLUMNS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
					arr[x_begin + 1][i] = bomb;
				}
			}
			//правый нижний угол
			else if (x_end == ROWS - 1 && y_end == COLUMNS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
			}
			//если корабль упирается в нижнюю часть поля
			else if (y_end + 1 <= COLUMNS - 1 && y_end - 1 >= 0 && x_end == ROWS - 1)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin - 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
			}
			//если корабль упирается в верхнюю часть поля
			else if (y_begin - 1 > 0 && y_end + 1 < COLUMNS - 1 && x_begin - 1 <= 0)
			{
				//before
				arr[x_begin][y_begin - 1] = bomb;
				arr[x_begin + 1][y_begin - 1] = bomb;
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//если корабль находится в левом верхнем углу
			else if (y_begin == 0 && x_begin == 0 && x_begin + 1 < ROWS - 1)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//если корабль упирается в левый край
			else if (y_begin == 0 && x_begin - 1 >= 0 && x_begin + 1 <= ROWS - 1)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin + 1][i] = bomb;
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
				arr[x_end + 1][y_end + 1] = bomb;
			}
			//если корабль в левом нижнем углу
			else if (y_begin == 0 && x_begin + 1 > ROWS - 1 && x_begin - 1 > 0)
			{
				for (int i = y_begin; i < y_begin + num_deck_ship; i++)
				{
					arr[x_begin - 1][i] = bomb;
				}
				//after
				arr[x_end][y_end + 1] = bomb;
				arr[x_end - 1][y_end + 1] = bomb;
			}
		}
	}

}

//перегрузка вывода данных об 1-ом корабле
ostream& operator <<(ostream&stream, const SHIP& obj)
{
	cout.setf(ios::boolalpha);				//флаг для вывода true/false словом
	stream << "Координаты носа: " << obj.x_begin + 1 << " " << obj.y_begin + 1
		<< " кормы: " << obj.x_end + 1 << " " << obj.y_end + 1 << endl;
	stream << "Статус: " << obj.alive << endl
		<< "Num deck: " << obj.num_deck_ship << endl
		<< "Num shot: " << obj.num_shot << endl;

	if (obj.dir_n == VERTICAL)
		stream << "Направление: вертикальное" << endl;
	else
		stream << "Направление: горизонтальное" << endl;
	for (int i = 0; i < obj.num_deck_ship; i++)
	{
		stream << obj.new_ship[i];		//вывод корабля
	}
	stream << endl;
	return stream;
}