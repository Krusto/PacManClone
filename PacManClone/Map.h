#pragma once
#include <cstdint>
#include <string>
#include "Point.h"

namespace PacMan {

	template <uint32_t SizeX, uint32_t SizeY>
	class Map {
	public:
		Map() = default;

		void Set(size_t x, size_t y, int8_t value) { m_Data[x][y] = value; }
		void Set(Point pos, int8_t value) { m_Data[(int)pos.x][(int)pos.y] = value; }
		int8_t Get(size_t x, size_t y) const { return m_Data[x][y]; }
		int8_t Get(Point pos) const { 
			if (pos.y < height && pos.x < width && pos.x >= 0 && pos.y >= 0) {
				return m_Data[(size_t)pos.x][(size_t)pos.y];
			}
			return INT8_MIN;
		}


		bool IsValid(Point pos) { return (pos.y < height && pos.x < width && pos.x >= 0 && pos.y >= 0); }
		auto& data() { return &m_Data; }

		auto GetSizeX() const { return SizeX; };
		auto GetSizeY() const { return SizeY; };

		const void Draw(Point playerPosition,Point ghostPosition[4], bool frightened[4]) const;
		void Fill(int8_t symbol);

		void Fill(std::string data[SizeY]);

		bool isColliding(Point p) { 
			char c = m_Data[(int)p.GetTrunc().x][(int)p.GetTrunc().y];
			return c == '#';
		}

	private:
		char m_Data[SizeX][SizeY]{};
		uint32_t width = SizeX, height = SizeY;
	};

}