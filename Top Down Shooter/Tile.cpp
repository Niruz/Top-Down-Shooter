#include "Tile.h"
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
Tile::Tile(float inX, float inY, bool blocking, bool spikedFloor, bool oneWay, bool isPillar, const std::string& tiletype)
	:myX(inX), myY(inY), myIsBlockingFlag(blocking), myG(0.0f), myF(0.0f), myH(0.0f), myParent(nullptr), isOccupied(false), isPlayerOnTile(false),
	myIsSpikedFloor(spikedFloor), myIsOneWayTile(oneWay), myIsPillar(isPillar), myTileType(tiletype)
{

}
void Tile::SetPosition(int x, int y)
{
	glm::mat4 translMat = glm::mat4(1.0f);
	myWorldPosition = glm::vec2(x, y);
	myAABB.myOrigin = myWorldPosition;
	myAABB.halfX = 16.0f;
	myAABB.halfY = 16.0f;
	glm::vec2 tilePos = glm::vec2(x, y);
	translMat = glm::translate(translMat, glm::vec3(x, y, 0.0f));

	glm::mat4 scaleMat = glm::mat4(1.0f);
	scaleMat = glm::scale(scaleMat, glm::vec3(16, 16, 16));
	myModelMatrix = translMat * scaleMat;

}




