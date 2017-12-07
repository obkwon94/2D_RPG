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

void StageLoader::CreateComponents()
{
	/*
	for (int i = 0; i< count; i++)
	{
		Component* component = CreateLifeNPC(L"monster", L"monster");
	}
	Player* player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	*/
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