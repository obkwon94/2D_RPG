#include "PathfindingMoveState.h"
#include "PathfindingImmediateState.h"
#include "PathfinderMonster.h"


PathfinderMonster::PathfinderMonster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename) :
	Monster(name, scriptName, textrueFilename)
{

}

PathfinderMonster::~PathfinderMonster()
{

}

void PathfinderMonster::UpdateAI(float deltaTime)
{
	Monster::UpdateAI(deltaTime);
}
/*
Component* PathfinderMonster::Collision(std::list<Component*>& collisionList)
{
	Monster::Collision(collisionList);

	return NULL;
}
*/