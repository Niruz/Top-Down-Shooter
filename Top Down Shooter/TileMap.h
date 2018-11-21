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
	Tile* GetTile2(int fromX, int fromY);

	void GetPath(int fromX, int fromY, int toY, int toX, std::vector<Tile*>& list);
	
	void GenerateGraph();

	bool validIndex(int checkX, int checkY);

	bool IsDirectionWalkable(int checkX, int checkY);
	bool IsDirectionJumpable(int checkX, int checkY);
	float map(float s, float a1, float a2, float b1, float b2);

	void printMap();
	void printPath(std::vector<Tile*>& aPathList);

	std::vector<Tile*>& GetMap();
	void setPlayerTile(float x, float y);

	Tile* lastPlayerTile;
	
private:

	bool PathFind(Tile* aStartTile, Tile* aGoalTile, std::vector<Tile*>& aPathList);

	int GetTileIndex(int x, int y);
	int GetDiagonalDistance(Tile* aStartTile, Tile* aGoalTile);
	int GetDiagonalDistance2(Tile* aStartTile, Tile* aGoalTile);
	std::vector<Tile*> myMapTiles;

	int myMapHeight;
	int myMapWidth;

};