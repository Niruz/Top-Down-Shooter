#include "AdventurerSprite.h"

AdventurerSprite::AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	// Adventurer V1
	myAnimations["AdventurerGetUpMelee"]       = new Animation(5, 0,    50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerKnockedDownMelee"] = new Animation(5, 5,    50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleePunch1"]      = new Animation(4, 10,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleePunch2"]      = new Animation(4, 14,    50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleePunch3"]      = new Animation(5, 18,    50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleeHurt"]        = new Animation(3, 23,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleeKick1"]       = new Animation(4, 26,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleeKick2"]       = new Animation(4, 30,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleeJump"]        = new Animation(4, 34,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerMeleeRun"]         = new Animation(6, 38,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerDrawSword"]        = new Animation(4, 44,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerSheatheSword"]     = new Animation(4, 48,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAirSlamBegin"]     = new Animation(4, 52,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAirSlamLoop"]      = new Animation(2, 56,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAirSlamEnd"]       = new Animation(3, 58,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerChannelSpell"]     = new Animation(4, 61,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerCastSpell"]        = new Animation(4, 65,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerDropKick"]         = new Animation(2, 69,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerDie"]              = new Animation(7, 71,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerBowGround"]        = new Animation(9, 78,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerBowInAir"]         = new Animation(6, 87,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerRunSword"]         = new Animation(6, 93,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerSlide"]            = new Animation(3, 99,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerStand"]            = new Animation(2, 102,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack3AirSword"]  = new Animation(3, 104,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack1AirSword"]  = new Animation(4, 107,   50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack2AirSword"]  = new Animation(3, 111,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack2Sword"]     = new Animation(6, 114,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack3Sword"]     = new Animation(6, 120,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerHurt"]             = new Animation(3, 126,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerAttack1Sword"]     = new Animation(5, 129,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerCrouch"]           = new Animation(4, 134,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerFall"]             = new Animation(2, 138,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerIdleSword"]        = new Animation(4, 140,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerIdleSheathe"]      = new Animation(4, 144,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerJump"]             = new Animation(4, 148,  50, 37, 7900, 37, 0, 0);
	myAnimations["AdventurerRun"]              = new Animation(6, 152,  50, 37, 7900, 37, 0, 0);

	//Adventurer V2
}
AdventurerSprite::~AdventurerSprite()
{

}