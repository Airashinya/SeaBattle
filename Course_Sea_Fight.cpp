// Course_Sea_Fight.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	Game play;
	play.start_game();


	return 0;
}