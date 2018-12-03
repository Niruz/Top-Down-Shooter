#include "UndeadWarriorSprite.h"

UndeadWarriorSprite::UndeadWarriorSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["UndeadWarriorAttack"] = new Animation(5, 0, 94, 36, 2350, 36, 0, 0);
	myAnimations["UndeadWarriorDie"] = new Animation(5, 7, 94, 36, 2350, 36, 0, 0);
	myAnimations["UndeadWarriorHurt"] = new Animation(3, 12, 94, 36, 2350, 36, 0, 0);
	myAnimations["UndeadWarriorIdle"] = new Animation(4, 15, 94, 36, 2350, 36, 0, 0);
	myAnimations["UndeadWarriorRun"] = new Animation(6, 19, 94, 36, 2350, 36, 0, 0);

}
UndeadWarriorSprite::~UndeadWarriorSprite()
{
}