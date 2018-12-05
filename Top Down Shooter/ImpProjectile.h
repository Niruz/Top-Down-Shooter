#pragma once

#include "BaseProjectileEntity.h"

struct ImpProjectile : public BaseProjectileEntity
{
	ImpProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~ImpProjectile() {};

	void Update();
	bool HandleMessage(const Message& msg);
};