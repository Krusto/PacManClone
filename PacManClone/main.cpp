#include <iostream>
#include <Windows.h>
#include "PacMan.h"
#include "WindowsFunctions.h"

int main() {

	ShowConsoleCursor(false);
	system("mode 23,23");

	PacMan::Game game;
	game.Init();

	while (true) {
		ClearScreen();
		game.Update();
		Sleep(100);
	}
	return 0;
}