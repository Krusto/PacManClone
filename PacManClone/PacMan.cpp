#include "PacMan.h"
#include "Map.cpp"
#include <Windows.h>
#include "WindowsFunctions.h"
void PacMan::Game::Init()
{
	m_Player.position ={ 2,2};
	m_OldPlayerPosition = { 2,2 };

	for (size_t i = 0; i < 4; i++)
	{
		m_Enemy[i].position = { 10,10};
		m_Enemy[i].id = i;
	}

	std::string mapSketch[] = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"#    .  #123#  .    #",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};
	m_Map.Fill(mapSketch);

}

void PacMan::Game::Update()
{
	if (!m_Player.isDead) {
		m_Ticks++;

		Point positions[4];
		bool frightened[4];
		for (size_t i = 0; i < 4; i++) {
			positions[i] = m_Enemy[i].position.GetTrunc();
			frightened[i] = m_Enemy[i].frightenedMode;
		}

		m_Map.Draw(m_Player.position.GetTrunc(), positions, frightened);

		if (m_Ticks > 20) {
			if (m_Enemy[0].movementMode == 0)
				for (size_t i = 0; i < 4; i++)
					m_Enemy[i].movementMode = 1;
		}

		m_Player.Update(m_Map,positions);

		for (size_t i = 0; i < 4; i++)
		{
			m_Enemy[i].frightenedMode = m_Player.isPowered;
			m_Enemy[i].Update(m_Map, m_Player, m_Enemy[i]);
		}
	}
	else {
		system("cls");
		std::cout << "Game Over\n";
	}
	std::cout << "Score : "<<m_Player.score<<'\n';

}
