#pragma once
#include "Point.h"
#include "Map.h"
#include <cstdlib>
namespace PacMan {
	/**
	* Клас Играч
	*/
	class Player {
	public:
		/**
		* Конструктор по подразбиране
		*/
		Player() = default;
		/**
		* Конструктор при който се задава началната позиция на играча
		*/
		Player(const Point startPosition) : position(startPosition) {}
		/**
		* Функция която мърда играча в дадена посока
		*/
		void Move(Point dir) { position += dir; };
		/**
		* Функция която опреснява играча и картата
		*/
		void Update(Map<21, 21>& map,Point ghostPositions[4]);

		/**
		* Флаг който служи за проверка дали играчът е умрял
		*/
		bool isDead{};
		/**
		* Позиция на играча
		*/
		Point position{};
		/**
		* Посока в която се движи играча
		*/
		uint32_t direction{};
		/**
		* Точки които е събрал играча
		*/
		uint32_t score{};
		/**
		* умножител на точки
		*/
		uint32_t scoreMultiplier{};
		/**
		* Изминали тикове
		*/
		uint32_t multiplierTicks{};
		/**
		* Флаг за проверка дали може да изяде духче
		*/
		bool isPowered{};
	};
}