#include "Stage.h"
#include "Map.h"
#include "Player.h"
#include "LifePlayer.h"
#include "LifeNPC.h"
#include "LifeStageLoader.h"

LifeStageLoader::LifeStageLoader(Stage* stage) :
	StageLoader(stage)
{
	_lifeNPCcount = 0;
}

LifeStageLoader::~LifeStageLoader()
{

}

void LifeStageLoader::CreateComponents()
{
	for (int i = 0; i < 150; i++)
	{
		CreateLifeNPC(L"npc", L"character_sprite2");
	}

	Player* player = new LifePlayer(L"Player", L"Player", L"Player");
	_stage->AddStageComponent(player);
	_stage->GetMap()->InitViewer(player);
}

Component* LifeStageLoader::CreateLifeNPC(std::wstring scriptName, std::wstring spriteName)
{
	SetName(L"life_npc", _lifeNPCcount);
	_lifeNPCcount++;
	Component* component = new LifeNPC(_name.c_str(), scriptName, spriteName);
	_stage->AddStageComponent(component);

	return component;
}