#include "SwordHitEffectSprite.h"

SwordHitEffectSprite::SwordHitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["SwordHitEffect1"]  = new Animation(10, 0,  64, 64, 1984, 64, 0, 0, 1);
	myAnimations["EnemyHitEffect2"]  = new Animation(11, 10, 64, 64, 1984, 64, 0, 0, 1);
	myAnimations["EnemyHitEffect3"]  = new Animation(10, 21, 64, 64, 1984, 64, 0, 0, 1);
}
SwordHitEffectSprite::~SwordHitEffectSprite()
{

}