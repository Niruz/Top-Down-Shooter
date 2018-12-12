#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 0,    50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 6,    50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 10,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 14,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 18,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 20,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 23,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 27,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 31,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 33,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 40,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 49,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 55,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 61,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 64,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 66,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 69,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 73,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 76,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 82,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 88,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 91,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 96,   50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 100,  50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 102,  50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 106,  50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 110,  50, 37, 6000, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 114,  50, 37, 6000, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}