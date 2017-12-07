#pragma once

#include "Player.h"

class PathfinderPlayer : public Player
{
public:
	PathfinderPlayer();
	~PathfinderPlayer();

	//AI
public:
	void UpdateAI(float deltaTime);
	void InitState();
};