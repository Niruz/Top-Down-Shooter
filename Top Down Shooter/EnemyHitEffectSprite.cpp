#include "EnemyHitEffectSprite.h"

EnemyHitEffectSprite::EnemyHitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["EnemyDeathEffect"] = new Animation(10, 0,  64, 64, 1920, 64, 0, 0, 1);
	myAnimations["EnemyHitEffect1"]  = new Animation(10, 10, 64, 64, 1920, 64, 0, 0, 1);
	myAnimations["EnemyHitEffect2"]  = new Animation(10, 20, 64, 64, 1920, 64, 0, 0, 1);
}
EnemyHitEffectSprite::~EnemyHitEffectSprite()
{

}