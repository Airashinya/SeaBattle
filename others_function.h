#pragma once
#include "stdafx.h"

//***************ПЕРЕВОД БУКВЫ В ЦИФРУ ПРИ ВВОДЕ КООРДИНАТ***************
int check_input_symb(char column);
//функция позволяет менять цвет изображений в консоли
void MyColor(int text, int background);
//****************ПОЛЕ БОЯ****************
//верхняя строка
void put_top_line(ostream& stream);
//внутренния строки 
void put_middle_line(ostream& stream);
//нижняя строка
void put_bottom_line(ostream& stream);
//вывод поля
ostream& battlefield(ostream&stream, char arr[][COLUMNS], char *name);

