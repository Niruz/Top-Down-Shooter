#include "Tile.h"

Tile::Tile(float inX, float inY, bool blocking)
	:myX(inX), myY(inY), myIsBlockingFlag(blocking), myG(0.0f), myF(0.0f), myH(0.0f), myParent(nullptr), isOccupied(false)
{

}