#pragma once
#include "Player.h"
#include "Map.h"
#include "Ghost.h"

namespace PacMan {
	class Game {
	public:
		Game() = default;
		void Init();
		void Update();
	private:
		Point m_OldPlayerPosition{};

		Player m_Player{};
		Ghost m_Enemy[4]{};
		Map<21,21> m_Map{};
		uint32_t m_Ticks{};
	};
}