#pragma once

#include "BaseProjectileEntity.h"

struct NecromancerProjectile : public BaseProjectileEntity
{
	NecromancerProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~NecromancerProjectile() {};

	void Update();
	bool HandleMessage(const Message& msg);
};