#pragma once
#include <Windows.h>

/**
* Функция която казва на курсора да отиде на x,y
*/
void GotoXY(SHORT x, SHORT y);
/**
* Функция която взима позицията на курсора
*/
POINT GetCursorPosition();
/**
* Функция която трие екрана
*/
void ClearScreen();
/**
* Функцуя която показва или скрива курсора
*/
void ShowConsoleCursor(bool showFlag);