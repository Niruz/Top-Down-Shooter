#include "Edge.h"
#include "Tile.h"

Edge::Edge(Tile* ownerTile, Tile* otherTile, int weight)
	:myOwnerTile(ownerTile), myOtherTile(otherTile), myWeight(weight)
{

}
Edge::Edge() 
{
	myOwnerTile = nullptr;
	myOtherTile = nullptr;
	myWeight = -1;
}