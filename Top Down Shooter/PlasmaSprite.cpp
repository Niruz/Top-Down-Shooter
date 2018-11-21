#include "PlasmaSprite.h"

PlasmaSprite::PlasmaSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["PlasmaExplode"] = new Animation(6, 0, 200, 200, 1200, 200,0,0);
}
PlasmaSprite::~PlasmaSprite()
{

}