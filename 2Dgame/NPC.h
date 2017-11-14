#pragma once

#include "Character.h"

class NPC : public Character
{
public:
	NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~NPC();

	void UpdateAI(float deltaTime);
};