#include "ComponentSystem.h"
#include "Map.h"
#include "Monster.h"
#include "NPC.h"
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

void Stage::Init(std::wstring name)
{
	_componentList.clear();

	_map = new Map(name.c_str());

	_componentList.push_back(_map);

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"recover_item_%d", i);
		RecoveryItem* item = new RecoveryItem(name, L"recovery_item", L"item_sprites");
		_componentList.push_back(item);
	}

	Player* player = new Player(L"player", L"player", L"player");
	_componentList.push_back(player);

	for (int i = 0; i < 20; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		NPC* npc = new NPC(name, L"npc", L"character_sprite2");
		_componentList.push_back(npc);
	}


	//NPC* npc = new NPC(L"npc", L"npc", L"character_sprite2");
	//_componentList.push_back(npc);

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Monster* monster = new Monster(name, L"monster", L"monster");
		_componentList.push_back(monster);
	}

	//Monster* monster = new Monster(L"monster", L"monster", L"monster");
	//_componentList.push_back(monster);

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