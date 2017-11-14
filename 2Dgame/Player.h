#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~Player();

	//AI
public:
	void UpdateAI(float deltaTime);
};