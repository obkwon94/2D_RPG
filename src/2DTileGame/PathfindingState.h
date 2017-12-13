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
public:
	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH
	};

private:
	std::queue<TileCell*> _pathfindingTileQueue;
	TileCell* _targetTileCell;
	eUpdateState _updateState;

	TileCell* _reverseTileCell;

public:
	void UpdatePathfinding();
	void UpdateBuildPath();
};
