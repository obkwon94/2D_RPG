#pragma once

#include "Player.h"

class PathfinderPlayer : public Player
{
public:
	PathfinderPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename);
	~PathfinderPlayer();

	// AI
public:
	void UpdateAI(float deltaTime);

	// State
public:
	void InitState();
};
