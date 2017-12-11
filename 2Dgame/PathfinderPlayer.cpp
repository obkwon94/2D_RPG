#include "IdleState.h"
#include "PathfindingState.h"
#include "PathfinderPlayer.h"

PathfinderPlayer::PathfinderPlayer(std::wstring name, std::wstring scriptName, std::wstring textureFileName) :
	Player(name, scriptName, textureFileName)
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