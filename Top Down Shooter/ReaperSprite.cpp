#include "ReaperSprite.h"

ReaperSprite::ReaperSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["ReaperAttack"] = new Animation(5, 0, 48, 46, 1296, 46, 0, 0);
	myAnimations["ReaperDie"] = new Animation(5, 11, 48, 46, 1296, 46, 0, 0);
	myAnimations["ReaperHurt"] = new Animation(3, 16, 48, 46, 1296, 46, 0, 0);
	myAnimations["ReaperIdle"] = new Animation(4, 19, 48, 46, 1296, 46, 0, 0);
	myAnimations["ReaperRun"] = new Animation(4, 23, 48, 46, 1296, 46, 0, 0);

}
ReaperSprite::~ReaperSprite()
{
}