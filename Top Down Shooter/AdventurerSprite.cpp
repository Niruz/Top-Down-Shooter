#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerWallRunMelee"]     = new Animation(6, 0,    50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerWallGlideMelee"]   = new Animation(2, 6,    50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerGetUpMelee"]       = new Animation(5, 8,    50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerKnockedDownMelee"] = new Animation(5, 13,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleePunch1"]      = new Animation(4, 18,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleePunch2"]      = new Animation(4, 22,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleePunch3"]      = new Animation(5, 26,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleeHurt"]        = new Animation(3, 31,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleeKick1"]       = new Animation(4, 34,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleeKick2"]       = new Animation(4, 38,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleeJump"]        = new Animation(4, 42,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 46,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 52,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 56,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 60,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 64,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 66,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 69,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 73,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 77,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 79,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 86,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 95,   50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 101,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 107,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 110,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 112,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 115,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 119,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 122,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 128,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 134,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 137,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 142,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 146,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 148,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 152,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 156,  50, 37, 8300, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 160,  50, 37, 8300, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}