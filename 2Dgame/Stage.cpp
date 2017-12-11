#include "ComponentSystem.h"
#include "Map.h"
#include "StageLoader.h"
#include "LifeStageLoader.h"
#include "DefaultStageLoader.h"
#include "Monster.h"
#include "NPC.h"
#include "LifeNPC.h"
#include "Player.h"
#include "LifePlayer.h"
#include "RecoveryItem.h"
#include "Stage.h"

Stage::Stage()
{
	_stageLoader.clear();
}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();

	for (std::map<std::wstring, StageLoader*>::iterator it = _stageLoader.begin(); it != _stageLoader.end(); it++)
	{
		StageLoader* loader = it->second;
		if (NULL != loader)
			delete loader;
	}
	_stageLoader.clear();
}

void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	_map = new Map(mapName.c_str());
	_componentList.push_back(_map);


	Player* player = NULL;
	
	{
		StageLoader* loader = new LifeStageLoader(this);
		_stageLoader[L"Mapdata03"] = loader;
	}
	{
		StageLoader* loader = new DefaultStageLoader(this);
		_stageLoader[L"default"] = loader;
	}

	std::map<std::wstring, StageLoader*>::iterator it = _stageLoader.find(mapName);
	if (it != _stageLoader.end())
		_stageLoader[mapName]->CreateComponents(mapName);
	else
		_stageLoader[L"default"]->CreateComponents(mapName);

	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Init();
	}
}

void Stage::Update(float deltaTime)
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	UpdateBaseComponentList();
	UpdateRemoveComponentList();
}

void Stage::Render()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Render();
	}
}

void Stage::Release()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Release();
	}
}

void Stage::Reset()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Reset();
	}
}

void Stage::CreateLifeNPC(Component* component)
{
	component->GetTileX();
	component->GetTileY();
	_createBaseComponentList.push_back(component);
}

void Stage::DestroyNPC(int tileX, int tileY, Component* tileCharacter)
{
	_map->ResetTileComponent(tileX, tileY, tileCharacter);

	_componentList.remove(tileCharacter);
	ComponentSystem::GetInstance()->RemoveComponent(tileCharacter);
}

void Stage::CheckDestroyNPC(Component* component)
{
	_removeComponentList.push_back(component);
}

void Stage::UpdateBaseComponentList()
{
	for (std::list<Component*>::iterator it = _createBaseComponentList.begin(); it != _createBaseComponentList.end(); it++)
	{
		Component* baseComponent = (*it);

		LifeNPC* npc = (LifeNPC*)(_stageLoader[_map->GetName()]->CreateLifeNPC(L"npc", L"character_sprite2"));

		npc->Init(baseComponent->GetTileX(), baseComponent->GetTileY());
	}
	_createBaseComponentList.clear();
}

void Stage::UpdateRemoveComponentList()
{
	for (std::list<Component*>::iterator it = _removeComponentList.begin(); it != _removeComponentList.end(); it++)
	{
		Component* com = (*it);
		DestroyNPC(com->GetTileX(), com->GetTileY(), com);
	}
	_removeComponentList.clear();
}

void Stage::AddStageComponent(Component* component)
{
	component->Init();
	_componentList.push_back(component);
}