#pragma once

#include <queue>
#include "TileCell.h"
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

	struct compare
	{
		bool operator()(TileCell* a, TileCell* b)
		{
			//return a->GetDistanceFromStart() > b->GetDistanceFromStart();
			return a->GetHeuristic() > b->GetHeuristic();
		}
	};

private:
	//std::queue<TileCell*> _pathfindingTileQueue;
	std::priority_queue<TileCell*, std::vector<TileCell*>, compare> _pathfindingTileQueue;
	TileCell* _targetTileCell;
	eUpdateState _updateState;

	TileCell* _reverseTileCell;
	
public:
	void UpdatePathfinding();
	void UpdateBuildPath();

	float CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell);
	float CalcComplectHeuristic(TileCell* nextTileCell, TileCell* targetTileCell);
	float CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell);
};
