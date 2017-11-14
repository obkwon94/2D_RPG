#include "ComponentSystem.h"
#include "Map.h"
#include "MoveState.h"
#include "Monster.h"

Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Character(name, scriptName, textureFileName)
{
	_type = eComponentType::CT_MONSTER;

	int speed = (rand() % 500) + 100;
	_moveTime = (float)speed / 1000.0f;
}
Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	if (false == _isLive)
		return;

	
	if (false == _state->isMoving())
	{
		std::vector<eComponentType> compareTypeList;
		compareTypeList.push_back(eComponentType::CT_NPC);
		compareTypeList.push_back(eComponentType::CT_PLAYER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 6, compareTypeList);

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
			else if (findEnemy->GetTileY() <= _tileY)
			{
				direction = eDirection::UP;
			}
			else if (_tileY <= findEnemy->GetTileY())
			{
				direction = eDirection::DOWN;
			}
			//MoveStart(direction);

			if (eDirection::NONE != direction)
			{
				_currentDirection = direction;
				//MoveStart();
				_state->Start();
			}
		}
		else
		{
			Character::UpdateAI(deltaTime);
		}
	}
}

void Monster::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		Component* com = (*it);
		if ((com->GetType() == eComponentType::CT_NPC) || (com->GetType() == eComponentType::CT_PLAYER))
		{
			sComponentMsgParam msgParam;
			msgParam.sender = this;
			msgParam.message = L"Attack";
			msgParam.receiver = (*it);
			msgParam.attackPoint = _attackPoint;
			ComponentSystem::GetInstance()->SendMsg(msgParam);
		}
	}
}