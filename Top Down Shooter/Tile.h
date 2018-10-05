#pragma once
#include <vector>

struct Tile
{
	Tile(float inX, float inY, bool blocking);
	~Tile(){}
	float myX;
	float myY;

	bool myIsBlockingFlag;
	//TODO: use this later when adding several AIs to avoid stacking
	//The idea is, get a list of tiles as my path
	//On every frame move close to the next tile in the list
	//But if its occupied, we simply wait
	//They might still stack if they move to the same tile from two adjacent tiles,
	//Maybe use a pointer to the person occupying the tile
	//Then set an Entity as the owner before it starts moving and then just check
	//If isOccupied && entityOccupying != me
	//dont move
	//else
	//move
	//They will probably stand in line to defeat the player
	//So if the tile is occupied AND the distance to the player is less than some radius
	//We can try getting a new path
	bool isOccupied;
	bool playerTile;//Maybe not needed
	float myG, myF, myH;

	Tile* myParent;

	std::vector<Tile*> myNeighbours;

};