#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerWallGlideMelee"]   = new Animation(2, 0,    50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerGetUpMelee"]       = new Animation(5, 2,    50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerKnockedDownMelee"] = new Animation(5, 7,    50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleePunch1"]      = new Animation(4, 12,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleePunch2"]      = new Animation(4, 16,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleePunch3"]      = new Animation(5, 20,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleeHurt"]        = new Animation(3, 25,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleeKick1"]       = new Animation(4, 28,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleeKick2"]       = new Animation(4, 32,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleeJump"]        = new Animation(4, 36,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 40,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 46,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 50,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 54,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 58,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 60,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 63,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 67,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 71,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 73,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 80,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 89,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 95,   50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 101,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 103,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 106,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 109,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 113,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 116,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 122,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 128,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 131,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 136,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 140,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 142,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 146,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 150,  50, 37, 8000, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 154,  50, 37, 8000, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}