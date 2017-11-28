#pragma once

#include "Character.h"

class NPC : public Character
{
public:
	NPC(std::wstring name, std::wstring scriptName, std::wstring textureFileName);
	~NPC();

	void UpdateAI(float deltaTime);
};