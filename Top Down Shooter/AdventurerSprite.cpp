#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 0,   50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 4,   50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 6,   50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 9,   50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 13,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 17,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 19,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 26,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 35,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 41,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 47,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 50,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 52,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 55,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 59,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 62,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 68,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 74,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 77,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 82,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 86,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 88,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 92,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 96,  50, 37, 5300, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 100, 50, 37, 5300, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}