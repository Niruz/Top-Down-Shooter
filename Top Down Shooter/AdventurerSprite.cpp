#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerAttack3AirSword"] = new Animation(3, 0,    50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"] = new Animation(4, 3,    50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"] = new Animation(3, 7,    50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]    = new Animation(6, 10,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]    = new Animation(6, 16,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerHurt"]            = new Animation(3, 22,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]    = new Animation(5, 25,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerCrouch"]          = new Animation(4, 30,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerFall"]            = new Animation(2, 34,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]       = new Animation(4, 36,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]     = new Animation(4, 40,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerJump"]            = new Animation(4, 44,   50, 37, 2700, 37, 0, 0);
	myAnimations["AdventurerRun"]             = new Animation(6, 48,   50, 37, 2700, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}