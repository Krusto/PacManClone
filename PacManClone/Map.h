#pragma once
#include <cstdint>
#include <string>
#include "Point.h"

namespace PacMan {

	template <uint32_t SizeX, uint32_t SizeY>
	class Map {
	public:
		/**
		* Конструктор по подразбиране
		*/
		Map() = default;

		/**
		* Функция която задава стойност на клетка с позиция х,у
		*/
		void Set(size_t x, size_t y, int8_t value) { m_Data[x][y] = value; }
		/**
		* Функция която задава стойност на клетка с позиция pos
		*/
		void Set(Point pos, int8_t value) { m_Data[(int)pos.x][(int)pos.y] = value; }
		/**
		* Функция която връща стойност на клетка с позиция х,у
		*/
		int8_t Get(size_t x, size_t y) const { return m_Data[x][y]; }
		/**
		* Функция която връща стойност на клетка с позиция pos
		*/
		int8_t Get(Point pos) const {
			if (pos.y < height && pos.x < width && pos.x >= 0 && pos.y >= 0) {
				return m_Data[(size_t)pos.x][(size_t)pos.y];
			}
			return INT8_MIN;
		}

		/**
		* Функция която проверява дали точката е в картата
		*/
		bool IsValid(Point pos) { return (pos.y < height && pos.x < width && pos.x >= 0 && pos.y >= 0); }
		/**
		* Функция която връща низа с информация на картата
		*/
		auto& data() { return &m_Data; }

		/**
		* Функция която връща широчина на картата
		*/
		auto GetSizeX() const { return SizeX; };
		/**
		* Функция която връща височина на картата
		*/
		auto GetSizeY() const { return SizeY; };
		/**
		* Функция която рисува
		*/
		const void Draw(Point playerPosition,Point ghostPosition[4], bool frightened[4]) const;
		/**
		* Функция която запълва картата с някакъв символ
		*/
		void Fill(int8_t symbol);

		/*
		* Функция която запълва картата с някакъв низ от редове
		*/
		void Fill(std::string data[SizeY]);

		/**
		* Функция която проверява дали позицията се намира на мястото на стена
		*/
		bool isColliding(Point p) { 
			char c = m_Data[(int)p.GetTrunc().x][(int)p.GetTrunc().y];
			return c == '#';
		}

	private:
		/**
		* Низ с информацията за картата
		*/
		char m_Data[SizeX][SizeY]{};
		/**
		* Широчина на картата
		*/
		uint32_t width = SizeX;
		/**
		* Височина на картата
		*/
		uint32_t height = SizeY;
	};

}