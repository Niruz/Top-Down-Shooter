#pragma once

#include "BaseProjectileEntity.h"

struct AdventurerProjectileArrow : public BaseProjectileEntity
{
	AdventurerProjectileArrow(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~AdventurerProjectileArrow() {};

	void Update();
	bool HandleMessage(const Message& msg);
};