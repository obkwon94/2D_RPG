#include "IdleState.h"
#include "PathfinderPlayer.h"

PathfinderPlayer::PathfinderPlayer()
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
	ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindingState());
}