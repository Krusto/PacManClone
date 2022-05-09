#include "Player.h"
#include "WindowsFunctions.h"
void PacMan::Player::Update(Map<21, 21>& map,Point ghostPositions[4])
{
	if (multiplierTicks > 0) {
		multiplierTicks--;
	}
	else {
		isPowered = false;
		scoreMultiplier = 1;
	}

	if (map.Get(position) == '.') {
		score += 1 * scoreMultiplier;
		map.Set(position, ' ');
	}
	else if (map.Get(position) == 'o') {
		score += 5;
		map.Set(position, ' ');
		scoreMultiplier = 10;
		multiplierTicks = 30;
	}
	else if (map.Get(position) == 'P') {
		score += 20;
		map.Set(position, ' ');
		scoreMultiplier = 20;
		multiplierTicks = 15;
		isPowered = true;
	}

	for (size_t i = 0; i < 4; i++)
	{
		if (ghostPositions[i] == position && isPowered) {
			score += 100;
			scoreMultiplier = 30;
			multiplierTicks = 15;
		}
	}

	bool wallExist[4]{0,0,0,0};

	wallExist[0] = map.Get(position + Point{1, 0}) == '#'; // DOWN
	wallExist[1] = map.Get(position + Point{0, -1}) == '#'; // LEFT
	wallExist[2] = map.Get(position + Point{-1, 0}) == '#'; // UP
	wallExist[3] = map.Get(position + Point{0, 1}) == '#'; // RIGHT

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (!wallExist[0])
			direction = 0;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!wallExist[1])
			direction = 1;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if (!wallExist[2])
			direction = 2;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if(!wallExist[3])
			direction = 3;
	}

	float speed = 1;
	if (!wallExist[direction])
	{
		switch (direction)
		{
		case 0:
		{
			position.x  += speed;

			break;
		}
		case 1:
		{
			position.y -= speed;

			break;
		}
		case 2:
		{
			position.x -= speed;

			break;
		}
		case 3:
		{
			position.y += speed;
		}
		}
	}

}
