#pragma once

#include <queue>
#include "State.h"

class Character;
class TileCell;

class PathfindingState : public State
{
public:
	PathfindingState();
	~PathfindingState();

public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();

	// Pathfinding
private:
	std::queue<TileCell*> _pathfindingTileQueue;
	TileCell* _targetTileCell;
};
