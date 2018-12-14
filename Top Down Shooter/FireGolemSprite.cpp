#include "FireGolemSprite.h"

FireGolemSprite::FireGolemSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	/*myAnimations["FireGolemAttack1"] = new Animation(7, 0, 64, 57,  2944, 57, 0, 0);
	myAnimations["FireGolemAttack2"] = new Animation(10, 7, 64, 57, 2944, 57, 0, 0);
	myAnimations["FireGolemDie"]     = new Animation(9, 17, 64, 57, 2944, 57, 0, 0);
	myAnimations["FireGolemHurt"]    = new Animation(3, 26, 64, 57, 2944, 57, 0, 0);
	myAnimations["FireGolemIdle"]    = new Animation(5, 29, 64, 57, 2944, 57, 0, 0);
	myAnimations["FireGolemRun"]     = new Animation(6, 34, 64, 57, 2944, 57, 0, 0);
	myAnimations["FireGolemSlam"]    = new Animation(5, 41, 64, 57, 2944, 57, 0, 0);*/
	myAnimations["FireGolemAttack1"] = new Animation(7, 0,  128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemAttack2"] = new Animation(10, 7, 128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemDie"]     = new Animation(9, 17, 128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemHurt"]    = new Animation(3, 26, 128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemIdle"]    = new Animation(5, 29, 128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemRun"]     = new Animation(6, 34, 128, 114, 5888, 114, 0, 0);
	myAnimations["FireGolemSlam"]    = new Animation(5, 41, 128, 114, 5888, 114, 0, 0);
	//use firegolemsheet5 for old vesrion
}
FireGolemSprite::~FireGolemSprite()
{

}