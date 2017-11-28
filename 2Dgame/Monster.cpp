#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "MoveState.h"
#include "Monster.h"

Monster::Monster(std::wstring name, std::wstring scriptName, std::wstring textureFileName) : Character(name, scriptName, textureFileName)
{
	_type = eComponentType::CT_MONSTER;

	int speed = (rand() % 100) + 100;
	_moveTime = (float)speed / 1000.0f;
}
Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

	std::vector<eComponentType> compareTypeList;
	compareTypeList.push_back(eComponentType::CT_NPC);
	compareTypeList.push_back(eComponentType::CT_PLAYER);
	Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(map, this, 6, compareTypeList);
	
	if (NULL != findEnemy)
	{
		//추격 방향 설정
		eDirection direction = eDirection::NONE;
					
		
		if (findEnemy->GetTileX() <= _tileX)
		{
			direction = eDirection::LEFT;
		}
		else if (_tileX <= findEnemy->GetTileX())
		{
			direction = eDirection::RIGHT;
		}
	
		if (findEnemy->GetTileY() <= _tileY)
		{
			direction = eDirection::UP;
		}
		else if (_tileY <= findEnemy->GetTileY())
		{
			direction = eDirection::DOWN;
		}
	
		
		if (eDirection::NONE != direction)
		{
			_currentDirection = direction;
			_state->NextState(eStateType::ET_MOVE);
		}
		
		
	}
	else
	{
		Character::UpdateAI(deltaTime);
	}	
}

Component* Monster::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		Component* com = (*it);
		if ((com->GetType() == eComponentType::CT_NPC) || (com->GetType() == eComponentType::CT_PLAYER))
		{
			return (*it);
		}
	}
	//ChangeState(eStateType::ET_IDLE);
	return NULL;
}