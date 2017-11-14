#include "ComponentSystem.h"
#include "Map.h"
#include "MoveState.h"
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
	if (false == _state->isMoving())
	{
		/*���� �������� �� ĭ�� Ÿ���� �������� �����Ͽ� �˻��ϴ� Ÿ�� ������ ���Ѵ�*/
		/*���� �� ��� Ÿ���� �˻��Ͽ� NPC or Player �� ������ ���� �����Ѵ�*/
		/*��ã������ ��� �����δ�*/
		
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
					/*
					direction = (eDirection)findDir;
					MoveStart(direction);
					*/
					_currentDirection = (eDirection)findDir;
					//MoveStart();
					_state->Start();
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