#include "Stage.h"
#include "Map.h"
#include "Player.h"
#include "NPC.h"
#include "Monster.h"
#include "RecoveryItem.h"

#include "DefaultStageLoader.h"

DefaultStageLoader::DefaultStageLoader(Stage* stage) :
	StageLoader(stage)
{

}

DefaultStageLoader::~DefaultStageLoader() 
{

}

void DefaultStageLoader::createComponents()
{

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"recovery_item_%d", i);
		RecoveryItem* item = new RecoveryItem(name, L"recovery_item", L"item_sprites");
		_stage.AddStageComponent(item);
	}

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		NPC* npc = new NPC(name, L"npc", L"character_sprite2");
		_stage.AddStageComponent(npc);
	}

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Monster* monster = new Monster(name, L"monster", L"monster");
		_stage.AddStageComponent(monster);
	}

	Player* player = new Player(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	_stage->GetMap()->InitViewer(player);
}