#pragma once
#include <Windows.h>

void GotoXY(SHORT x, SHORT y);
POINT GetCursorPosition();
void ClearScreen();
void ShowConsoleCursor(bool showFlag);