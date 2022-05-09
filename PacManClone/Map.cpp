#include "Map.h"
#include <iostream>
#include <Windows.h>
#include "WindowsFunctions.h"
namespace PacMan {
	template <uint32_t SizeX, uint32_t SizeY>
	const void Map<SizeX, SizeY>::Draw(Point playerPosition,Point ghostPosition[4],bool frightened[4]) const{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		for (size_t x = 0; x < SizeX; x++)
		{
			for (size_t y = 0; y < SizeY; y++)
			{
				if (playerPosition == Point(x,y)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					std::cout << '@';
				}else if (ghostPosition[0] == Point(x, y)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					if(frightened[0])
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					std::cout << '+';
				}
				else if (ghostPosition[1] == Point(x, y)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					if (frightened[1])
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					std::cout << '+';
				}
				else if (ghostPosition[2] == Point(x, y)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					if (frightened[2])
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					std::cout << '+';
				}
				else if (ghostPosition[3] == Point(x, y)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					if (frightened[3])
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					std::cout << '+';
				}
				else {
					SetConsoleTextAttribute(out, 15);
					std::cout << (char)m_Data[x][y];
				}
				
			}
			std::cout << '\n';
		}
	}

	template<uint32_t SizeX, uint32_t SizeY>
	void PacMan::Map<SizeX, SizeY>::Fill(int8_t symbol)
	{
		for (size_t x = 0; x < SizeX; x++)
		{
			for (size_t y = 0; y < SizeY; y++)
			{
				m_Data[x][y] = symbol;
			}
		}
	}

	template<uint32_t SizeX, uint32_t SizeY>
	void Map<SizeX, SizeY>::Fill(std::string data[SizeY])
	{
		for (size_t x = 0; x < SizeX; x++)
		{
			for (size_t y = 0; y < SizeY; y++)
			{
				m_Data[x][y] = data[x][y];
			}
		}
	}
}