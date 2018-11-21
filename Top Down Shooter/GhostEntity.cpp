#include "SimpleTimer.h"
#include "GhostEntity.h"
#include "Group.h"
#include "GhostSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaGhostStates.h"
#include "StateMachine.h"
#include "PlasmaSprite.h"
GhostEntity::GhostEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo) :
	BaseEnemy(id, name, myStartPosition, patrolTo), myAtTarget(false)
{
	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myAnimatedSprite = new GhostSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(37, 65), TextureMan->GetTexture("ghost"), Heading::LEFTFACING);
	

	myAnimatedSprite->SetAnimation("GhostDie");
	myXDirection = 1.0f;



	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myPlasmaSprite = new PlasmaSprite(glm::vec4(mPosition.x+6.0f, mPosition.y, 0.089f, 1), glm::vec2(200, 200), TextureMan->GetTexture("plasma"), Heading::LEFTFACING);
	mySprite->Add(myPlasmaSprite);
	mySprite->Add(myAnimatedSprite);
	myPlasmaSprite->SetAnimation("PlasmaExplode");

	myStateMachine = new StateMachine<GhostEntity>(this);

	myStateMachine->setCurrentState(GhostPatrol::Instance());
	myStateMachine->changeState(GhostPatrol::Instance());

}
GhostEntity::~GhostEntity()
{

}
void GhostEntity::Update()
{
	myStateMachine->update();
}
bool GhostEntity::HandleMessage(const Message& msg)
{
	return false;
}
void GhostEntity::HandleMovement()
{
	if (myXDirection > 0.0f)
	{
		if (mPosition.y <= endPatrol.y)
		{
			mPosition.y += myXDirection;
			myAnimatedSprite->myPosition.y = mPosition.y;
		}
		else
		{
			myXDirection = -1.0f;
			//myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
			myAtTarget = true;
		}
	}
	if (myXDirection < 0.0f)
	{
		if (mPosition.y >= startPatrol.y)
		{
			mPosition.y += myXDirection;
			myAnimatedSprite->myPosition.y = mPosition.y;
		}
		else
		{
			myXDirection = 1.0f;
			//myAnimatedSprite->SetHeading(Heading::LEFTFACING);
		}
	}
	myPlasmaSprite->myPosition.y = mPosition.y;

	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition, 1.0f);
}
void GhostEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void GhostEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTime();
}