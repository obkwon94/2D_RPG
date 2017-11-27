#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "LifeTileObject.h"

LifeTileObject::LifeTileObject(LPCWSTR name, Sprite* sprite) :
	TileObject(name, sprite)
{

}

LifeTileObject::~LifeTileObject()
{

}

void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);

	// 주변 8칸을 탐색 - 캐릭터가 몇마리 있는지
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

	int range = 1;

	std::vector<eComponentType> compareTypeList;
	compareTypeList.push_back(eComponentType::CT_NPC);
	Component* findCharacter = ComponentSystem::GetInstance()->FindComponentInRange(map, this, range, compareTypeList);
}