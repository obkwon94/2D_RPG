#include "ComponentSystem.h"
#include "Map.h"
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

	
	if (false == _isMoving)
	{
		/*
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
		
		int fileOffset = 6;
		int minTileX = _tileX - fileOffset;
		int maxTileX = _tileX + fileOffset;
		int minTileY = _tileY - fileOffset;
		int maxTileY = _tileY + fileOffset;

		if (minTileX < 0)
			minTileX = 0;
		if (map->GetWidth() <= maxTileX)
			maxTileX = map->GetWidth()-1;
		if (minTileY < 0)
			minTileX = 0;
		if (map->GetHeight() <= maxTileY)
			maxTileY = map->GetHeight()-1;

		Component* findEnemy = NULL;

		//탐색거리에 적이 있는 지 확인
		for (int y = minTileY; y <= maxTileY; y++)
		{
			
			for (int x = minTileX; x <= maxTileX; x++)
			{
				std::list<Component*> componentList;
				if (false == map->GetTileCollisionList(x, y, componentList))
				{
					for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
					{
						Component* component = (*it);
						if ((component->GetType() == eComponentType::CT_NPC) ||
							(component->GetType() == eComponentType::CT_PLAYER))
						{
							findEnemy = component;
							break;
						}
					}
				}
				if (NULL != findEnemy)
					break;
			}
			if (NULL != findEnemy)
				break;
		}
		*/

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
			MoveStart(direction);
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
			//ComponentSystem::GetInstance()->SendMsg(L"Attack", (*it), msgParam);
			ComponentSystem::GetInstance()->SendMsg(msgParam);
		}
	}
}