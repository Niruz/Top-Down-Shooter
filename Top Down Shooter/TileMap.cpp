#include "TileMap.h"
#include <string>
#include <fstream>
#include <iostream>

TileMap::TileMap(const std::string& name)
{
	if (!InitializeFromMap(name))
		std::cout << "\nCould not initialize map with name: " + name + "\n" << std::endl;
}
TileMap::~TileMap()
{
	for (std::list<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		myMapTiles.remove(tile);
		delete tile;
	}
}
bool TileMap::InitializeFromMap(const std::string& name)
{
	std::string line;
	std::ifstream myfile(name.c_str());
	if (!myfile.is_open())
		return false;

	int lineIndex = 0;
	while( !myfile.eof())
	{
		std::getline(myfile, line);
		for(unsigned int i = 0;i < line.length(); i++)
		{
			Tile* tile = new Tile(i, lineIndex, (line[i] == 'X'));
			myMapTiles.push_back(tile);
		}
		lineIndex++;
	}

	myfile.close();
	return true;
}
void TileMap::GetPath(int fromX, int fromY, int toY, int toX, std::list<Tile*>& list)
{
	Tile* fromTile = GetTile(fromX, fromY);
	Tile* toTile = GetTile(toY, toX);

	for (std::list<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		tile->myIsVisitedFlag = false;
	}
	PathFind(fromTile, toTile, list);

}
bool TileMap::PathFind(Tile* aFromTile, Tile* aToTile, std::list<Tile*>& aList)
{
	aFromTile->myIsVisitedFlag = true;

	if (aFromTile->myIsBlockingFlag)
		return false;

	if (aFromTile == aToTile)
		return true;
}
void TileMap::printMap()
{
	int lastY = 0;
	for( std::list<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		if (tile->myY != lastY)
		{
			std::cout << "\n";
			lastY++;
		}
		if (tile->myIsBlockingFlag)
			std::cout << "X";
		else
			std::cout << ".";
	}
}
Tile* TileMap::GetTile(int fromX, int fromY)
{
	for (std::list<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++) 
	{
		Tile* tile = *iterator;
		if(tile->myX == fromX && tile->myY == fromY)
		{
			return tile;
		}
	}
	return nullptr;
}