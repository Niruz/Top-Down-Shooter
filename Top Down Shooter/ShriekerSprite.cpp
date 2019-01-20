#include "ShriekerSprite.h"

ShriekerSprite::ShriekerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["ShriekerAppear"] = new Animation(6, 0,  64, 80, 1600, 80, 0, 0);
	myAnimations["ShriekerIdle"]   = new Animation(7, 6,  64, 80, 1600, 80, 0, 0);
	myAnimations["ShriekerShriek"] = new Animation(4, 13, 64, 80, 1600, 80, 0, 0, 12);
	myAnimations["ShriekerVanish"] = new Animation(8, 17, 64, 80, 1600, 80, 0, 0);
}
ShriekerSprite::~ShriekerSprite()
{

}