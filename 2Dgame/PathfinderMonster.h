#pragma once

#include "Monster.h"

class PathfinderMonster : public Monster
{
public:
	PathfinderMonster(std::wstring name, std::wstring scriptName, std::wstring textureFileName);
	~PathfinderMonster();

public:
	void UpdateAI(float deltaTime);
};