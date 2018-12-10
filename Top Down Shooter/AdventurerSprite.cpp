#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerDropKick"]        = new Animation(2, 0,     50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerDie"] =             new Animation(7, 2,     50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerBowGround"]       = new Animation(9, 9,     50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]        = new Animation(6, 18,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerRunSword"]        = new Animation(6, 24,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerSlide"]           = new Animation(3, 30,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerStand"]           = new Animation(2, 33,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"] = new Animation(3, 35,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"] = new Animation(4, 38,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"] = new Animation(3, 42,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]    = new Animation(6, 45,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]    = new Animation(6, 51,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerHurt"]            = new Animation(3, 57,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]    = new Animation(5, 60,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerCrouch"]          = new Animation(4, 66,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerFall"]            = new Animation(2, 69,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]       = new Animation(4, 71,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]     = new Animation(4, 75,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerJump"]            = new Animation(4, 79,    50, 37, 4450, 37, 0, 0);
	myAnimations["AdventurerRun"]             = new Animation(6, 83,    50, 37, 4450, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}