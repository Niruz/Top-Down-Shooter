#pragma once

#include "BaseProjectileEntity.h"

class ShakeInfo;
struct EarthProjectile : public BaseProjectileEntity
{
	EarthProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~EarthProjectile() { delete myShakeInfoBasicAttack; };

	void Update();
	bool HandleMessage(const Message& msg);

	ShakeInfo* myShakeInfoBasicAttack;
};