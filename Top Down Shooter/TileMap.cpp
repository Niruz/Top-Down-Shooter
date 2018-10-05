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


	/*for(int h = 0; h < myMapTiles.size(); h++)
	{
		Tile* currentTile = myMapTiles[h];
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0)
					continue;

				int checkX = currentTile->myX + i;
				int checkY = currentTile->myY + j;

				if (validIndex(checkX,checkY))
				{
					if(!currentTile->myIsBlockingFlag)
						currentTile->myNeighbours.push_back(GetTile2(checkX, checkY));
				}
			}
		}

	}*/

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


	for(int i = 0; i < mapHeight; i++)
	{
		for(int k = 0; k < mapWidth; k++)
		{
			int currentIndex = (i * mapWidth) + k;

			//int testIndex = GetTileIndex(i, k)
			//No need to process blocking walls
			if (myMapTiles[currentIndex]->myIsBlockingFlag)
				continue;
			Tile* currentTile = myMapTiles[currentIndex];
			//the locations we need to access
			int NW = currentIndex - mapWidth - 1;
			int N = currentIndex - mapWidth;
			int NE = currentIndex - mapWidth + 1;
			int E = currentIndex + 1;
			int SE = currentIndex + mapWidth + 1;
			int S = currentIndex + mapWidth;
			int SW = currentIndex + mapWidth - 1;
			int W = currentIndex - 1;


		/*	if (NW < 0)
				currentTile->myNorthWest = nullptr;
			else
				currentTile->myNorthWest = myMapTiles[NW];

			if (N < 0 )
				currentTile->myNorth = nullptr;
			else
				currentTile->myNorth = myMapTiles[N];

			if (NE < 0 )
				currentTile->myNorthEast = nullptr;
			else
				currentTile->myNorthEast = myMapTiles[NE];

			if (!myMapTiles[E]->myIsBlockingFlag)
				currentTile->myEast = myMapTiles[E];
			if (!myMapTiles[SE]->myIsBlockingFlag)
				currentTile->mySouthEast = myMapTiles[SE];
			if (!myMapTiles[S]->myIsBlockingFlag)
				currentTile->mySouth = myMapTiles[S];
			if (!myMapTiles[SW]->myIsBlockingFlag)
				currentTile->mySouthWest = myMapTiles[SW];
			if (!myMapTiles[W]->myIsBlockingFlag)
				currentTile->myWest = myMapTiles[W];*/
			
			//Later check so that we dont check outside the map, the borders are closed for now
		/*	if (!myMapTiles[NW]->myIsBlockingFlag)
				currentTile->myNorthWest = myMapTiles[NW];
			if (!myMapTiles[N]->myIsBlockingFlag)
				currentTile->myNorth = myMapTiles[N];
			if (!myMapTiles[NE]->myIsBlockingFlag)
				currentTile->myNorthEast = myMapTiles[NE];
			if (!myMapTiles[E]->myIsBlockingFlag)
				currentTile->myEast = myMapTiles[E];
			if (!myMapTiles[SE]->myIsBlockingFlag)
				currentTile->mySouthEast = myMapTiles[SE];
			if (!myMapTiles[S]->myIsBlockingFlag)
				currentTile->mySouth = myMapTiles[S];
			if (!myMapTiles[SW]->myIsBlockingFlag)
				currentTile->mySouthWest = myMapTiles[SW];
			if (!myMapTiles[W]->myIsBlockingFlag)
				currentTile->myWest = myMapTiles[W];*/
			int shiter = 5;

		}
		int hoho = 5;
	}

	int shit = 5;
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