#include "TileMap.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include "TextureManager.h"
#include "ShaderManager.h"
TileMap::TileMap(const std::string& name)
{
	if (!InitializeFromMap(name))
		std::cout << "\nCould not initialize map with name: " + name + "\n" << std::endl;
	lastPlayerTile = nullptr;
}
TileMap::~TileMap()
{
	for (std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		delete tile;
	}
	myMapTiles.clear();
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

	GenerateGraph();

	return true;
}
int TileMap::GetTileIndex(int x, int y)
{
	return (y * myMapWidth) + x;
}
bool TileMap::validIndex(int checkX, int checkY)
{
	return (checkX >= 0 && checkX < myMapWidth && checkY >= 0 && checkY < myMapHeight);
}
bool TileMap::IsDirectionWalkable(int checkX, int checkY)
{
	if (!validIndex(checkX, checkY))
		return false;
	return !myMapTiles[GetTileIndex(checkX, checkY)]->myIsBlockingFlag;
}
void TileMap::GenerateGraph()
{
	float mapHeight = myMapTiles.back()->myY + 1;
	float mapWidth = myMapTiles.back()->myX + 1;

	myMapHeight = myMapTiles.back()->myY + 1;
	myMapWidth = myMapTiles.back()->myX + 1;


	for(int h = 0; h < myMapTiles.size(); h++)
	{
		Tile* currentTile = myMapTiles[h];

		if (currentTile->myX == 1 && currentTile->myY == 1)
			int bp = 5;
		bool northWalkable = false;
		bool eastWalkable = false;
		bool southWalkable = false;
		bool westWalkable = false;

		bool northEastWalkable = false;
		bool northWestWalkable = false;
		bool southEastWalkable = false;
		bool southWestWalkable = false;
		
		northWalkable = IsDirectionWalkable(currentTile->myX, currentTile->myY - 1);
		eastWalkable = IsDirectionWalkable(currentTile->myX + 1, currentTile->myY );
		southWalkable = IsDirectionWalkable(currentTile->myX, currentTile->myY + 1);
		westWalkable = IsDirectionWalkable(currentTile->myX-1, currentTile->myY);

		//clockwise from NE.. not blocking, not corner case, valid index
		northEastWalkable = IsDirectionWalkable(currentTile->myX + 1, currentTile->myY - 1);
		northWestWalkable = IsDirectionWalkable(currentTile->myX - 1, currentTile->myY - 1);
		southEastWalkable = IsDirectionWalkable(currentTile->myX + 1, currentTile->myY + 1);
		southWestWalkable = IsDirectionWalkable(currentTile->myX - 1, currentTile->myY + 1);
		
		if(northWalkable)
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX, currentTile->myY - 1));
		if (eastWalkable)
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX + 1, currentTile->myY));
		if (southWalkable)
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX, currentTile->myY + 1));
		if (westWalkable)
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX - 1, currentTile->myY));
		
		if(northWalkable && eastWalkable && northEastWalkable)
		{
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX + 1, currentTile->myY - 1));
		}
		if(eastWalkable && southWalkable && southEastWalkable)
		{
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX + 1, currentTile->myY + 1));
		}
		if(southWalkable && westWalkable && southWestWalkable)
		{
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX - 1, currentTile->myY + 1));
		}
		if(westWalkable && northWalkable && northWestWalkable)
		{
			currentTile->myNeighbours.push_back(GetTile2(currentTile->myX - 1, currentTile->myY - 1));
		}
		int shit = 5;

	}

	float startX = -32.0f * 10.0f;
	float startY = 32.0f * 6;
	for (int i = 0; i < myMapTiles.size(); i++)
	{
		if (i % 20 == 0)
		{
			startY -= 32.0f;
			startX = -32.0f*10.0f;
		}
		myMapTiles[i]->SetPosition(startX, startY);
		startX += 32.0f;
	}
}
void TileMap::GetPath(int fromX, int fromY, int toY, int toX, std::vector<Tile*>& list)
{
	//Tile* fromTile = GetTile(fromX, fromY);
	Tile* fromTile = GetTile2(fromX, fromY);
	//Tile* toTile = GetTile(toY, toX);
	Tile* toTile = GetTile2(toY, toX);

	for (std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		tile->myParent = nullptr;
	}
	PathFind(fromTile, toTile, list);

}
bool TileMap::PathFind(Tile* aStartTile, Tile* aGoalTile, std::vector<Tile*>& aPathList)
{
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;

	openList.push_back(aStartTile);

	aStartTile->myG = 0.0f;
	aStartTile->myH = GetDiagonalDistance2(aStartTile, aGoalTile);
	aStartTile->myF = aStartTile->myG + aStartTile->myH;

	while(!openList.empty())
	{
		Tile* currentTile = nullptr;
		//Find the tile with the lowest F score
		float currentF = std::numeric_limits<float>::max();
		int index = -1;
		for (int i = 0; i < openList.size(); ++i)
		{
			if(openList[i]->myF < currentF)
			{
				index = i;
				currentF = openList[i]->myF;
				currentTile = openList[i];
			}
		}
		closedList.push_back(openList[index]);
		openList.erase(openList.begin() + index);

		if(currentTile == aGoalTile)
		{
			Tile* temp = currentTile;
			aPathList.push_back(temp);
			while (temp->myParent)
			{
				aPathList.push_back(temp->myParent);
				temp = temp->myParent;
			}
			std::cout << "DONE!\n";
		//	find = true;
			return true;
		}


		for(int h = 0; h < currentTile->myNeighbours.size(); h++)
		{
			//Tile* neighbour = GetTile2(checkX, checkY);
			Tile* neighbour = currentTile->myNeighbours[h];

			//Tile* testerino = GetTile2(checkX, checkY);

			//TODO: optimize away this and keep a bool instead
			bool inClosed = false;
			for (int k = 0; k < closedList.size(); k++)
			{
				if (neighbour == closedList[k])
					inClosed = true;
			}

			if (!inClosed)
			{
				int tempG = currentTile->myG + GetDiagonalDistance2(currentTile, neighbour);

				bool inOpen = false;
				for (int k = 0; k < openList.size(); k++)
				{
					if (openList[k] == neighbour)
						inOpen = true;
				}

				if (inOpen)
				{
					if (tempG < neighbour->myG)
					{
						neighbour->myG = tempG;
						neighbour->myParent = currentTile;
					}
				}
				else
				{
					neighbour->myG = tempG;
					openList.push_back(neighbour);
					//	std::push_heap(openSet.begin(), openSet.end());
					neighbour->myParent = currentTile;
				}
				neighbour->myH = GetDiagonalDistance2(neighbour, aGoalTile);
				neighbour->myF = neighbour->myG + neighbour->myH;

			}
		}					
		
	}

	return false;
}
int TileMap::GetDiagonalDistance(Tile* aStartTile, Tile* aGoalTile) 
{
	int dX = std::abs(aStartTile->myX - aGoalTile->myX);
	int dY = std::abs(aStartTile->myY - aGoalTile->myY);

	//dX *= 10;
	//dY *= 10;

	int D = 10;
	int D2 = 14;

	int min = std::min(dX, dY);
	int result = D * (dX + dY) + (D2 - 2 * D) * std::min(dX, dY);
	return D * (dX + dY) + (D2 - 20 * D) * std::min(dX, dY);
	//return D * (dX + dY) + (D2 - 2 * D) * std::min(dx, dy)
}
int TileMap::GetDiagonalDistance2(Tile* aStartTile, Tile* aGoalTile)
{
	int dstX = std::abs(aStartTile->myX - aGoalTile->myX);
	int dstY = std::abs(aStartTile->myY - aGoalTile->myY);

	if (dstX > dstY)
		return 14 * dstY + 10 * (dstX - dstY);
	return 14 * dstX + 10 * (dstY - dstX);
}
void TileMap::printMap()
{
	int lastY = 0;
	std::cout << "\n";
	for( std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
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
	std::cout << "\n";
}
Tile* TileMap::GetTile(int fromX, int fromY)
{
	for (std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		if(tile->myX == fromX && tile->myY == fromY)
		{
			return tile;
		}
	}
	return nullptr;
}
Tile* TileMap::GetTile2(int fromX, int fromY)
{
	return myMapTiles[GetTileIndex(fromX, fromY)];
}
void TileMap::printPath(std::vector<Tile*>& aPathList)
{
	std::cout << "\n";
	int lastY = 0;
	for (std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;

		bool isPath = false;
		for(int i = 0; i < aPathList.size(); i++)
		{
			if (tile == aPathList[i])
				isPath = true;
		}
		if (tile->myY != lastY)
		{
			std::cout << "\n";
			lastY++;
		}
		if (isPath)
			std::cout << "o";
		else if (tile->myIsBlockingFlag)
			std::cout << "X";
		else
			std::cout << ".";
	}
	std::cout << "\n";
}
std::vector<Tile*>& TileMap::GetMap()
{
	return myMapTiles;
}
float TileMap::map(float s, float a1, float a2, float b1, float b2)
{
	return b1 + (s - a1)*(b2 - b1) / (a2 - a1);
}
void TileMap::setPlayerTile(float x, float y)
{

	glm::vec2 playerPos(x, y);

	float shitX = this->map(playerPos.x, -320, 288, 0, 19);
	float shitY = this->map(playerPos.y, 160, -192, 0, 11);


	float roundX2 = round(shitX);
	float roundY2 = round(shitY);

	
	if (lastPlayerTile != nullptr)
		lastPlayerTile->isPlayerOnTile = false;


	//comment out this and add the commented below it
	lastPlayerTile = GetTile2(roundX2, roundY2);
	
/*	float lastClosest = 999999.0f;
	for (std::vector<Tile*>::iterator iterator = myMapTiles.begin(); iterator != myMapTiles.end(); iterator++)
	{
		Tile* tile = *iterator;
		glm::vec2 temp = playerPos - tile->myWorldPosition;
		float length = glm::length(temp);
		if (length < 32.0f  && length < lastClosest)
		{
			lastClosest = length;


			//tile->isPlayerOnTile = true;

			lastPlayerTile = tile;
			//break;
		}
		
	}*/
	lastPlayerTile->isPlayerOnTile = true;

}