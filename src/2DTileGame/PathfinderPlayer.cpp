#include "IdleState.h"
#include "PathfindingState.h"
#include "PathfindingMoveState.h"
#include "PathfinderPlayer.h"


PathfinderPlayer::PathfinderPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename) :
	Player(name, scriptName, textrueFilename)
{
}

PathfinderPlayer::~PathfinderPlayer()
{
}

void PathfinderPlayer::UpdateAI(float deltaTime)
{
}

void PathfinderPlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathfindingMoveState());
	//ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindingState());
}
