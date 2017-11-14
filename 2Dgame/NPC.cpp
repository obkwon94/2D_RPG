#include "ComponentSystem.h"
#include "Map.h"
#include "NPC.h"

NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Character(name, scriptName, textureFileName)
{
	_type = eComponentType::CT_NPC;

	int speed = (rand() % 1000) + 100;
	_moveTime = (float)speed / 1000.0f;
}
NPC::~NPC()
{

}

void NPC::UpdateAI(float deltaTime)
{
	if (false == _isMoving)
	{
		/*���� �������� �� ĭ�� Ÿ���� �������� �����Ͽ� �˻��ϴ� Ÿ�� ������ ���Ѵ�*/
		/*���� �� ��� Ÿ���� �˻��Ͽ� NPC or Player �� ������ ���� �����Ѵ�*/
		/*��ã������ ��� �����δ�*/
		
		
		/*
		int range = 5;
		int minTileX = _tileX - range;
		int maxTileX = _tileX + range;
		int minTileY = _tileY - range;
		int maxTileY = _tileY + range;

		if (minTileX < 0)
			minTileX = 0;
		if (map->GetWidth() <= maxTileX)
			maxTileX = map->GetWidth() - 1;
		if (minTileY < 0)
			minTileX = 0;
		if (map->GetHeight() <= maxTileY)
			maxTileY = map->GetHeight() - 1;

		Component* findEnemy = NULL;


		//Ž���Ÿ��� ���� �ִ� �� Ȯ��
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
						if ((component->GetType() == eComponentType::CT_MONSTER))
						{
							findEnemy = component;
							break;
						}
					}
				}

			}

		}
		*/
		std::vector<eComponentType> compareTypeList;
		compareTypeList.push_back(eComponentType::CT_MONSTER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 3, compareTypeList);

		if (NULL != findEnemy)
		{
			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");

			//���� ��� Ž��
			eDirection direction = eDirection::NONE;
			for (int findDir = 0; findDir < 4; findDir++)
			{
				int newTileX = _tileX;
				int newTileY = _tileY;

				switch(findDir)
				{
				case eDirection::LEFT:
					newTileX--;
					break;

				case eDirection::RIGHT:
					newTileX++;
					break;

				case eDirection::UP:
					newTileY--;
					break;

				case eDirection::DOWN:
					newTileY++;
					break;
				}

				if (map->CanMoveTileMap(newTileX, newTileY))
				{
					direction = (eDirection)findDir;
					MoveStart(direction);
					break;
				}
			}
		}
		else
		{
			Character::UpdateAI(deltaTime);
		}
	}
}
/*
void NPC::ReceiveMessage(std::wstring message, const sComponentMsgParam& msgParam)
{
	if (false == _isLive)
		return;

	if (L"Attack" == message)
	{
		int attackPoint = msgParam.attackPoint;
		_hp -= attackPoint;
		if (_hp <= 0)
		{
			_isLive = false;
			SetCanMove(true);

			//stop
			_moveDistancePerTimeX = 0.0f;
			_moveDistancePerTimeY = 0.0f;
		}
	}
}
*/