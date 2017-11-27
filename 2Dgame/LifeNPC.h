#pragma once
#include "Character.h"

class LifeNPC : public Character
{
public:
	LifeNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~LifeNPC();

	void UpdateAI(float deltaTime);
};