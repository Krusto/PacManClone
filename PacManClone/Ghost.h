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

		/**
		* Функция за движение на духчето в някаква посока
		*/
		void Move(Point dir) { position += dir; }

		/**
		* Функция която връща разстоянието до целта
		*/
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

		/**
		* Функция която проверява дали има колизия м-у духчето и пакман
		*/
		bool IsCollidingPacman(Player& player) {
			return player.position.GetTrunc() == position;
		}
		/**
		* Функция която опреснява целта
		*/
		void UpdateTarget(uint32_t pacmanDirection, Point ghostPosition, Point pacmanPosition,Map<21,21>& map) {
				if (movementMode == 0) // scatter mode
				{
					//отива в края на картата
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
					case 0: //червеният дух нацелва пакман
					{
						target = pacmanPosition;

						break;
					}
					case 1: //розовият дух нацелва 4 клетки пред пакман
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
					case 2: // синият нацелва 2 клетки пред пакман
					{
						target = pacmanPosition;

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

						target += {target.x - ghostPosition.x, 
							         target.y - ghostPosition.y};

						break;
					}
					case 3: // оранжевият дух преследва пакман и след това отива в scatter режим
					{
						
						if ( GetDistance(pacmanPosition,position) >= 4)
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
		/**
		* Функция за опресняване на духчето
		*/
		void Update(Map<21, 21>& map, Player& player,Ghost& ghost) {
			bool move = 0;

			unsigned char available_ways = 0;
			float speed = 1;

			bool walls[4]{};

			UpdateTarget(player.direction,ghost.position, player.position,map);

			walls[0] = map.Get(position + Point{ speed,0 }) == '#';
			walls[1] = map.Get(position + Point{ 0,-speed }) == '#';
			walls[2] = map.Get(position + Point{ -speed,0 }) == '#';
			walls[3] = map.Get(position + Point{ 0,speed }) == '#';

			if (frightenedMode != 1)
			{
				unsigned char optimal_direction = 4;

				// духчето може да мърда
				move = 1;

				for (unsigned char a = 0; a < 4; a++)
				{
					//духчетата не могат да се обърнат, стига да не е нужно
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
							// оптималната посока за да стигне целта
							optimal_direction = a;
						}
					}
				}

				if (available_ways > 1)
				{
					// когато стигне кръстопът избира най добрата посока
					direction = optimal_direction;
				}
				else
				{
					if (optimal_direction == 4)
					{
						// обръща се духчето на обратно защото трябва
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
				unsigned char random_direction = rand() % 4;

				if (frightenedSpeedTimer == 0)
				{
					
					move = 1;

					frightenedSpeedTimer = 30;

					for (unsigned char a = 0; a < 4; a++)
					{
						// не може да се обръщат дори и да се страхуват
						if (a == (2 + direction) % 4)
						{
							continue;
						}
						else if (walls[a] == 0)
						{
							available_ways++;
						}
					}

					if (available_ways > 0)
					{
						while (walls[random_direction] == 1 || random_direction == (2 + direction) % 4)
						{
							// взимаме произволна посока докато не може да я използваме
							random_direction = rand() % 4;
						}

						direction = random_direction;
					}
					else
					{
						// ако няма друг път се обръща наобратно
						direction = (2 + direction) % 4;
					}
				}
				else
				{
					frightenedSpeedTimer--;
				}
			}
			// ако може да се мръдне го местим
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

				// когато мине през портала го пращаме от другата страна
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
				if (frightenedMode == 0) // когато не е уплашен и докосне пакман, играта приключва
				{
					player.isDead = 1;
				}
				else //иначе бяга към клетката
				{
					frightenedMode = 2;

					target = home;
				}
			}
		}
		/**
		* Идентификатор на духчето
		*/
		uint32_t id{};
		/**
		* Таймер за колко време се страхува
		*/
		uint32_t frightenedSpeedTimer{};
		/**
		* Променлива която служи за проверка дали е уплашено
		*/
		bool frightenedMode{};
		/**
		* Режим на движение
		*/
		uint32_t movementMode{0};
		/**
		* Позижия на духчето
		*/
		Point position{};
		/**
		* Позиция на къщата на духчето
		*/
		Point home{10,10};
		/**
		* Посока на духчето
		*/
		uint32_t direction{};
		/**
		* Цел на духчето
		*/
		Point target{};
	};
}