#include "Map.h"
#include "Stage.h"
#include "LifePlayer.h"
#include "LifeNPC.h"
#include "StageLoader.h"

StageLoader::StageLoader(Stage* stage)
{
	_stage = stage;
	//_lifeNPCcount = 0;
}

StageLoader::~StageLoader()
{

}

void StageLoader::CreateComponents(std::wstring mapName)
{
	Map* map = new Map(mapName.c_str());
	_stage->SetMap(map);
	_stage->AddStageComponent(map);
}

Component* StageLoader::CreateLifeNPC(std::wstring scriptName, std::wstring textureFileName)
{
	/*
	SetName(L"lifeNpc");
	_lifeNPCcount++;
	Component* component = new LifeNPC(_name.c_str(), L"monster", L"monster");
	_stage->AddStageComponent(component);

	return component;
	*/
	return NULL;
}


void StageLoader::SetName(std::wstring name, int id)
{
	WCHAR wname[256];
	wsprintf(wname, L"%s_%d", name, id);
	_name = wname;
}