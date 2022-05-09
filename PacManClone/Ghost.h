#pragma once
#include "Point.h"
#include <iostream>
#include <stdlib.h>
#include "Map.h"
#include "Math.h"
#include "Player.h"

namespace PacMan {
	class Ghost {
	public:
		Ghost() = default;

		void Move(Point dir,float speed = 1.0) { position += dir; }

		float GetTargetDistance(uint32_t direction) {
			float x = position.x;
			float y = position.y;

			switch (direction)
			{
			case 0:
			{
				x += 1;

				break;
			}
			case 1:
			{
				y -= 1;

				break;
			}
			case 2:
			{
				x -= 1;

				break;
			}
			case 3:
			{
				y += 1;
			}
			}
			return GetDistance({ x,y }, target);
		}

		bool IsCollidingPacman(Player& player) {
			return player.position.GetTrunc() == position;
		}
		void UpdateTarget(uint32_t pacmanDirection, Point ghostPosition, Point pacmanPosition,Map<21,21>& map) {
				if (movementMode == 0) // scatter mode
				{
					//goes to corner
					switch (id)
					{
					case 0:
					{
						target = {(map.GetSizeX() - 1.0f), 0.0f };

						break;
					}
					case 1:
					{
						target = { 0.0f, 0.0f };

						break;
					}
					case 2:
					{
						target = { (map.GetSizeX() - 1.0f), (map.GetSizeY() - 1.0f) };

						break;
					}
					case 3:
					{
						target = { 0.0f,(map.GetSizeY() - 1.0f) };
					}
					}
				}
				else //chase mode
				{
					switch (id)
					{
					case 0: //The red gohst will chase Pacman.
					{
						target = pacmanPosition;

						break;
					}
					case 1: //The pink gohst will chase the 4th cell in front of Pacman.
					{
						target = pacmanPosition;

						switch (pacmanDirection)
						{
						case 0:
						{
							target += {2, 0};

							break;
						}
						case 1:
						{
							target -= {0, 2};

							break;
						}
						case 2:
						{
							target -= {2, 0};
							break;
						}
						case 3:
						{
							target += {0, 2};

						}
						}

						break;
					}
					case 2: //The blue gohst.
					{
						target = pacmanPosition;

						//Getting the second cell in front of Pacman.
						switch (pacmanDirection)
						{
						case 0:
						{
							target += {1, 0};

							break;
						}
						case 1:
						{
							target -= {0, 1};

							break;
						}
						case 2:
						{
							target -= {1, 0};

							break;
						}
						case 3:
						{
							target += {0, 1};
						}
						}

						//We're sending a vector from the red gohst to the second cell in front of Pacman.
						//Then we're doubling it.
						target += {target.x - ghostPosition.x, 
							         target.y - ghostPosition.y};

						break;
					}
					case 3: //The orange gohst will chase Pacman until it gets close to him. Then it'll switch to the scatter mode.
					{
						//Using the Pythagoras' theorem again.
						if (4 <= GetDistance(pacmanPosition,position))
						{
							target = pacmanPosition;
						}
						else
						{
							target = { 0.0f, (map.GetSizeY() - 1.0f) };
						}
					}
					}
				}
		}
		void Update(Map<21, 21>& map, Player& player,Ghost& ghost) {
			bool move = 0;

			//If this is greater than 1, that means that the gohst has reached the intersection.
			//We don't consider the way back as an available way.
			unsigned char available_ways = 0;
			float speed = 1;

			bool walls[4]{};

			UpdateTarget(player.direction,ghost.position, player.position,map);

			//This is so clean! I could spend hours staring at it.
			walls[0] = map.Get(position + Point{ speed,0 }) == '#';
			walls[1] = map.Get(position + Point{ 0,-speed }) == '#';
			walls[2] = map.Get(position + Point{ -speed,0 }) == '#';
			walls[3] = map.Get(position + Point{ 0,speed }) == '#';

			if (frightenedMode != 1)
			{
				//I used 4 because using a number between 0 and 3 will make the gohst move in a direction it can't move.
				unsigned char optimal_direction = 4;

				//The gohst can move.
				move = 1;

				for (unsigned char a = 0; a < 4; a++)
				{
					//Gohsts can't turn back! (Unless they really have to)
					if (a == (2 + direction) % 4)
					{
						continue;
					}
					else if (walls[a] == false)
					{
						if (optimal_direction == 4)
						{
							optimal_direction = a;
						}

						available_ways++;

						if (GetTargetDistance(a) < GetTargetDistance(optimal_direction))
						{
							//The optimal direction is the direction that's closest to the target.
							optimal_direction = a;
						}
					}
				}

				if (available_ways > 1)
				{
					//When the gohst is at the intersection, it chooses the optimal direction.
					direction = optimal_direction;
				}
				else
				{
					if (optimal_direction == 4)
					{
						//"Unless they have to" part.
						direction = (2 + direction) % 4;
					}
					else
					{
						direction = optimal_direction;
					}
				}
			}
			else
			{
				//I used rand() because I figured that we're only using randomness here, and there's no need to use a whole library for it.
				unsigned char random_direction = rand() % 4;

				if (frightenedSpeedTimer == 0)
				{
					//The gohst can move after a certain number of frames.
					move = 1;

					frightenedSpeedTimer = 30;

					for (unsigned char a = 0; a < 4; a++)
					{
						//They can't turn back even if they're frightened.
						if (a == (2 + direction) % 4)
						{
							continue;
						}
						else if (0 == walls[a])
						{
							available_ways++;
						}
					}

					if (available_ways > 0)
					{
						while (walls[random_direction] == 1 || random_direction == (2 + direction) % 4)
						{
							//We keep picking a random direction until we can use it.
							random_direction = rand() % 4;
						}

						direction = random_direction;
					}
					else
					{
						//If there's no other way, it turns back.
						direction = (2 + direction) % 4;
					}
				}
				else
				{
					frightenedSpeedTimer--;
				}
			}

			//If the gohst can move, we move it.
			if (move)
			{
				switch (direction)
				{
				case 0:
				{
					position.x += speed;

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

				//Warping.
				//When the gohst leaves the map, we move it to the other side.
				if (position.x <= -1)
				{
					position.x = map.GetSizeX() - speed;
				}
				else if (position.x >= map.GetSizeX())
				{
					position.x = speed;
				}
			}

			if (position.GetTrunc() == player.position.GetTrunc())
			{
				if (frightenedMode == 0) //When the gohst is not frightened and collides with Pacman, we kill Pacman.
				{
					player.isDead = 1;
				}
				else //Otherwise, the gohst starts running towards the house.
				{
					useDoor = 1;

					frightenedMode = 2;

					target = home;
				}
			}
		}
		uint32_t id{};
		uint32_t frightenedSpeedTimer{};
		bool frightenedMode{};
		bool useDoor{};
		uint32_t movementMode{0};
		Point position{};
		Point home{10,10};
		uint32_t direction{};
		Point target{};
	};
}