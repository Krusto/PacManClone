#pragma once
#include "Player.h"
#include "Map.h"
#include "Ghost.h"

namespace PacMan {
	class Game {
	public:
		/*
		* Конструктор по подразбиране
		*/
		Game() = default;
		/*
		* Функция за инициализация на играта
		*/
		void Init();
		/*
		* Функция която опреснява играта
		*/
		void Update();
	private:
		/*
		* Предишна позиция на играча
		*/
		Point m_OldPlayerPosition{};
		/*
		* Играч
		*/
		Player m_Player{};
		/*
		* Низ от духчета които се движат на картата
		*/
		Ghost m_Enemy[4]{};
		/*
		* Карта с размери [21,21]
		*/
		Map<21,21> m_Map{};
		/*
		* брой изминали тикове
		*/
		uint32_t m_Ticks{};
	};
}