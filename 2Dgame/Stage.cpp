#include "ComponentSystem.h"
#include "Map.h"
#include "Monster.h"
#include "NPC.h"
#include "LifeNPC.h"
#include "Player.h"
#include "RecoveryItem.h"
#include "Stage.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();
}

void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	_map = new Map(mapName.c_str());
	_componentList.push_back(_map);

	if (L"MapData03" == mapName)
	{
		_lifeNPCcount = 0;
		for (int i = 0; i < 70; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"lifeNPC%d", i);
			_lifeNPCcount++;
			LifeNPC* lifeNPC = new LifeNPC(name, L"npc", L"character_sprite2");
			_componentList.push_back(lifeNPC);

		}
	}
	else
	{
		for (int i = 0; i < 0; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"recover_item_%d", i);
			RecoveryItem* item = new RecoveryItem(name, L"recovery_item", L"item_sprites");
			_componentList.push_back(item);
		}



		for (int i = 0; i < 0; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"npc_%d", i);
			NPC* npc = new NPC(name, L"npc", L"character_sprite2");
			_componentList.push_back(npc);
		}


		//NPC* npc = new NPC(L"npc", L"npc", L"character_sprite2");
		//_componentList.push_back(npc);

		for (int i = 0; i < 0; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"monster_%d", i);
			Monster* monster = new Monster(name, L"monster", L"monster");
			_componentList.push_back(monster);
		}

		//Monster* monster = new Monster(L"monster", L"monster", L"monster");
		//_componentList.push_back(monster);
	}
	
	Player* player = new Player(L"player", L"player", L"player");
	_componentList.push_back(player);
	
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Init();
	}

	_map->InitViewer(player);
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
	/*
	WCHAR name[256];
	wsprintf(name, L"lifeNPC%d", _lifeNPCcount);
	_lifeNPCcount++;

	LifeNPC* lifeNPC = new LifeNPC(name, L"npc", L"character_sprite2");
	lifeNPC->Init(tileX, tileY);

	_componentList.push_back(lifeNPC);
	*/
	_createBaseComponentList.push_back(component);
}

void Stage::UpdateBaseComponentList()
{
	for (std::list<Component*>::iterator it = _createBaseComponentList.begin(); it != _createBaseComponentList.end(); it++)
	{
		Component* baseComponent = (*it);

		WCHAR name[256];
		wsprintf(name, L"lifeNPC%d", _lifeNPCcount);
		_lifeNPCcount++;

		LifeNPC* lifeNPC = new LifeNPC(name, L"npc", L"character_sprite2");
		lifeNPC->Init(baseComponent->GetTileX(), baseComponent->GetTileY());
		_componentList.push_back(lifeNPC);
	}
	_createBaseComponentList.clear();
}

void Stage::UpdateRemoveComponentList()
{
	for (std::list<Component*>::iterator it = _removeComponentList.begin(); it != _removeComponentList.end(); it++)
	{
		Component* com = (*it);
		DestroyLifeNPC(com->GetTileX(), com->GetTileY(), com);
	}

	_removeComponentList.clear();
}

void Stage::CheckDestroyLifeNPC(Component* component)
{
	_removeComponentList.push_back(component);
}

void Stage::DestroyLifeNPC(int tileX, int tileY, Component* component)
{
	_map->ResetTileComponent(tileX, tileY, component);

	component->SetCanMove(true);
	component->SetLive(false);

	_componentList.remove(component);
	ComponentSystem::GetInstance()->RemoveComponent(component);
}