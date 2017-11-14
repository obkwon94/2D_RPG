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
		/*나를 기준으로 몇 칸의 타일을 감시할지 결정하여 검사하는 타일 범위를 구한다*/
		/*범위 내 모든 타일을 검사하여 NPC or Player 가 있으면 적을 추적한다*/
		/*못찾았으면 평소 움직인다*/
		
		std::vector<eComponentType> compareTypeList;
		compareTypeList.push_back(eComponentType::CT_MONSTER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 3, compareTypeList);

		if (NULL != findEnemy)
		{
			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");

			//도주 경로 탐색
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