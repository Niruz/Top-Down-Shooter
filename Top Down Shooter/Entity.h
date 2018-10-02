#pragma once
#include <string>
#include "Message.h"

class Entity 
{
public:
	Entity(int id) 
	{
		setID(id);
	};
	Entity(int id, const std::string& name)
	{
		setID(id);
		setName(name);
	}

	virtual ~Entity() {};

	virtual void update() = 0;
	virtual bool handleMessage(const Message& msg) = 0;

	int getID() const
	{
		return mID;
	}
	std::string getName() const
	{
		return mName;
	}


private:
	int mID;
	//Optional name
	std::string mName;
	static int nextValidID;

	void setID(int val);
	void setName(const std::string& name);
};