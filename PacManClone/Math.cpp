#include "Math.h"
float GetDistance(PacMan::Point p1, PacMan::Point p2)
{
	return sqrt(pow(p2.x - p1.x, 2) +
		pow(p2.y - p1.y, 2) * 1.0);
}