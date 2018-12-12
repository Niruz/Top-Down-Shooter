#pragma once

#include "BaseProjectileEntity.h"

struct AdventurerProjectile : public BaseProjectileEntity
{
	AdventurerProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~AdventurerProjectile() {};

	void Update();
	bool HandleMessage(const Message& msg);
};