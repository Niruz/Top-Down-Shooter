#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerMeleeHurt"]        = new Animation(3, 0,    50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerMeleeKick1"]       = new Animation(4, 3,    50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerMeleeKick2"]       = new Animation(4, 7,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerMeleeJump"]        = new Animation(4, 11,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 15,    50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 21,    50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 25,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 29,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 33,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 35,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 38,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 42,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 46,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 48,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 55,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 64,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 70,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 76,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 79,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 81,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 84,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 88,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 91,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 97,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 103,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 106,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 111,   50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 115,  50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 117,  50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 121,  50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 125,  50, 37, 6750, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 129,  50, 37, 6750, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}