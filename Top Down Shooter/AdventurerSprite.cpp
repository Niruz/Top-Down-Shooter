#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerMeleePunch1"]      = new Animation(4, 0,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleePunch2"]      = new Animation(4, 4,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleePunch3"]      = new Animation(5, 8,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleeHurt"]        = new Animation(3, 13,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleeKick1"]       = new Animation(4, 16,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleeKick2"]       = new Animation(4, 20,    50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleeJump"]        = new Animation(4, 24,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 28,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 34,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 38,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 42,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 46,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 48,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 51,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 55,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 59,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 61,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 68,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 77,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 83,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 89,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 92,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 94,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 97,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 101,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 104,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 110,   50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 116,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 119,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 124,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 128,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 130,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 134,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 138,  50, 37, 7400, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 142,  50, 37, 7400, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}