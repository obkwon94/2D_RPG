#include "PathfindingImmediateState.h"

PathfindingImmediateState::PathfindingImmediateState()
{

}

PathfindingImmediateState::~PathfindingImmediateState()
{

}

void PathfindingImmediateState::Start()
{
	PathfindingState::Start();

	while (0 != _pathfindingTileQueue.size())
	{
		if (eUpdateState::BUILD_PATH == _updateState)
			break;
		UpdatePathfinding();
	}

	while (_reverseTileCell)
	{
		UpdateBuildPath();
	}
}
