#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerChannelSpell"]    = new Animation(4, 0,     50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]       = new Animation(4, 4,     50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerDropKick"]        = new Animation(2, 8,     50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerDie"] =             new Animation(7, 10,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerBowGround"]       = new Animation(9, 17,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]        = new Animation(6, 26,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerRunSword"]        = new Animation(6, 32,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerSlide"]           = new Animation(3, 38,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerStand"]           = new Animation(2, 41,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"] = new Animation(3, 43,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"] = new Animation(4, 46,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"] = new Animation(3, 50,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]    = new Animation(6, 53,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]    = new Animation(6, 59,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerHurt"]            = new Animation(3, 65,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]    = new Animation(5, 68,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerCrouch"]          = new Animation(4, 73,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerFall"]            = new Animation(2, 77,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]       = new Animation(4, 79,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]     = new Animation(4, 83,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerJump"]            = new Animation(4, 87,    50, 37, 4850, 37, 0, 0);
	myAnimations["AdventurerRun"]             = new Animation(6, 91,    50, 37, 4850, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}