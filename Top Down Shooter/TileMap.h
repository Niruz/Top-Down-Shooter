#pragma once
#include "Tile.h"
#include <string>

class TileMap
{
public:
	TileMap(){}
	TileMap(const std::string& name);
	~TileMap();

	bool InitializeFromMap(const std::string& name);
	Tile* GetTile(int fromX, int fromY);

	void GetPath(int fromX, int fromY, int toY, int toX, std::list<Tile*>& list);
	


	void printMap();
	
private:

	bool PathFind(Tile* aFromTile, Tile* aToTile, std::list<Tile*>& aList);

	std::list<Tile*> myMapTiles;
};