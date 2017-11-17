#pragma once

#include "Character.h"

class Monster : public Character
{
public:
	Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~Monster();

	

	//move
public:
	void UpdateAI(float deltaTime);
	Component* Collision(std::list<Component*>& collisionList);
};