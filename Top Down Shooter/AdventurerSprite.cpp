#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerAttack"]         = new Animation(5, 0, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerCrouch"]         = new Animation(4, 5, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerFall"]           = new Animation(2, 9, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]      = new Animation(4, 11, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]    = new Animation(4, 15, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerIdleJump"]       = new Animation(4, 19, 50, 37, 1450, 37, 0, 0);
	myAnimations["AdventurerIdleRun"]        = new Animation(6, 23, 50, 37, 1450, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}