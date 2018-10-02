#pragma once
#include <list>

struct Tile
{
	Tile(float inX, float inY, bool blocking)
		:myX(inX), myY(inY), myIsBlockingFlag(blocking), myIsVisitedFlag(false)
	{
	}
	~Tile(){}
	float myX;
	float myY;

	bool myIsBlockingFlag;
	bool myIsVisitedFlag;

	//4 entries for now, 8 later
	//N, NE, E, SE, S, SW, W , NW 
	std::list<Tile*> myNeighbours;
};