#pragma once

#include "Monster.h"

class PathfinderMonster : public Monster
{
public:
	PathfinderMonster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename);
	~PathfinderMonster();

public:
	void UpdateAI(float deltaTime);
	//Component* Collision(std::list<Component*>& collisionList);

};
