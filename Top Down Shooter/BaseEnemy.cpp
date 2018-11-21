
#include "BaseEnemy.h"
#include "Group.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"

BaseEnemy::BaseEnemy(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: Entity(id, name), startPatrol(myStartPosition), endPatrol(patrolTo), mPosition(myStartPosition), myAttackTimer(0.0f)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 16.0f, 16.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, 0.2f, 1.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
};
