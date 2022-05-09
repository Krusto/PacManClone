#pragma once
#include "Point.h"
#include "Map.h"
#include <cstdlib>
namespace PacMan {

	class Player {
	public:
		Player() = default;
		Player(const Point startPosition) : position(startPosition) {}

		void Move(Point dir) { position += dir; };
		void Update(Map<21, 21>& map,Point ghostPositions[4]);

		bool isDead{};
		Point position{};
		uint32_t direction{};
		uint32_t score{};
		uint32_t scoreMultiplier{};
		uint32_t multiplierTicks{};
		bool isPowered{};
	};
}