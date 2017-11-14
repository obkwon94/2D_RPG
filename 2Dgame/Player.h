#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~Player();

	//transform
public:
	//void MoveDeltaPosition(float deltaX, float deltaY);

	//AI
public:
	void UpdateAI(float deltaTime);

	//move
public:
	//void UpadateMove(float deltaTime);
};