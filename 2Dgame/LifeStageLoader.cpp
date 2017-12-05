#include "Stage.h"
#include "LifePlayer.h"
#include "LifeNPC.h"
#include "LifeStageLoader.h"

LifeStageLoader::LifeStageLoader(Stage* stage)
{
	_stage = stage;
	_lifeNPCcount = 0;
}

LifeStageLoader::~LifeStageLoader()
{

}

void LifeStageLoader::CreateComponents(int count)
{
	for (int i = 0; i< count; i++)
	{
		Component* component = CreateLifeNPC(L"monster", L"monster");
	}
	Player* player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
}

Component* LifeStageLoader::CreateLifeNPC(LPCWSTR scriptName, LPCWSTR textureFileName)
{
	SetName(L"lifeNpc");
	_lifeNPCcount++;
	Component* component = new LifeNPC(_name.c_str(), L"monster", L"monster");
	_stage->AddStageComponent(component);

	return component;
}

void LifeStageLoader::SetName(LPCWSTR name)
{
	WCHAR wname[256];
	wsprintf(wname, L"%s_%d", name, _lifeNPCcount);
	_name = wname;
}