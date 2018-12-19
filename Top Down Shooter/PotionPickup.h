#pragma once
#include "Pickup.h"
#include <string>

class PotionPickup : public Pickup
{
public:
	PotionPickup(int id, const std::string& name, const glm::vec3& myStartPosition, const std::string& texture);
	~PotionPickup() {};

	void Update();
	bool HandleMessage(const Message& msg);


	//HP, mana etc
	
};