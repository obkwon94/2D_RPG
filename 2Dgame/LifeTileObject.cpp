#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "LifeTileObject.h"

LifeTileObject::LifeTileObject(int tileX, int tileY, std::wstring name, Sprite* sprite) :
	TileObject(name, sprite)
{
	_tileX = tileX;
	_tileY = tileY;
}

LifeTileObject::~LifeTileObject()
{

}

void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);

	// 주변 8칸을 탐색 - 캐릭터가 몇마리 있는지
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

	int surroundedCharacter = 0;
	int range = 1;
	int minTileX = _tileX - range;
	int maxTileX = _tileX + range;
	int minTileY = _tileY - range;
	int maxTileY = _tileY + range;
	//bool isTileCharacter = false;
	Component* tileCharacter = NULL;

	if (minTileX < 0)
		minTileX = 0;
	if (map->GetWidth() <= maxTileX)
		maxTileX = map->GetWidth() -1;
	if (minTileY < 0)
		minTileY = 0;
	if (map->GetHeight() <= maxTileY)
		maxTileX = map->GetHeight() - 1;

	for (int y = minTileY; y <= maxTileY; y++)
	{
		for (int x = minTileX; x <= maxTileX; x++)
		{
			if (x != _tileX || y != _tileY)
			{
				std::list<Component*> componentList;
				if (false == map->GetTileCollisionList(x, y, componentList))
				{
					for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
					{
						Component* component = (*it);
						switch (component->GetType())
						{
						case eComponentType::CT_NPC:
						case eComponentType::CT_PLAYER:
							//isTileCharacter = true;
							tileCharacter = component;
							break;
						}
					}
				}
			}
		}
	}

	if (3 == surroundedCharacter)
	{
		//if (false == isTileCharacter)
		if (NULL == tileCharacter)
		{
			GameSystem::GetInstance()->GetStage()->CreateLifeNPC(_tileX, _tileY);
		}
	}
	else if (2 == surroundedCharacter)
	{
		//skip
	}
	else
	{
		//dead
		if (NULL == tileCharacter)
		{
			if (eComponentType::CT_PLAYER != tileCharacter->GetType())
			{
				GameSystem::GetInstance()->GetStage()->DestroyLifeNPC(_tileX, _tileY, tileCharacter);
				tileCharacter = NULL;
			}

		}
	}
}