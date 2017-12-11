#pragma once

#include "Player.h"

class PathfinderPlayer : public Player
{
public:
	PathfinderPlayer(std::wstring name, std::wstring scriptName, std::wstring textureFileName);
	~PathfinderPlayer();

	//AI
public:
	void UpdateAI(float deltaTime);
	void InitState();
};