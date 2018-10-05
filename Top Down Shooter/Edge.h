#pragma once

class Tile;

struct Edge
{
	Edge(Tile* ownerTile, Tile* otherTile, int weight);
	Edge();

	Tile* myOwnerTile;
	Tile* myOtherTile;
	int myWeight;
};