#include "UtilitiesSYS.h"
#include <iostream>
#include <Windows.h>
using namespace std;


void chcp1252()
{
	system("chcp 1252");
}

void clear_screen()
{
	system("cls");
}

void pause()
{
	system("pause");
}
 
uint8 colors[10] = { 0, 12, 10, 9, 14, 13, 3, 15, 8, 11 };
// black(0), red(12), green(10), blue(9), yellow(14), magenta(13), cian2(3), white(15), grey(8), cian1(11) 

void colorCTA(uint8 color, uint8 background)  // background is a digit
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (colors[background] << 4));
}