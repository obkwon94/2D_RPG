#pragma once
#include "Character.h"

class LifeNPC : public Character
{
public:
	LifeNPC(std::wstring name, std::wstring scriptName, std::wstring textureFileName);
	~LifeNPC();

	void UpdateAI(float deltaTime);
};