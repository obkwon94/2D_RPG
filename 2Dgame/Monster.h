#pragma once

#include "Character.h"

class Monster : public Character
{
public:
	Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~Monster();

	void UpdateAI(float deltaTime);

	//move
public:
	void Collision(std::list<Component*>& collisionList);
};