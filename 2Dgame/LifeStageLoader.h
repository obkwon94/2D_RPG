#pragma once
#include "StageLoader.h"

class LifeStageLoader : public StageLoader
{
public:
	LifeStageLoader(Stage* stage);
	~LifeStageLoader();

private:
	int _lifeNPCcount;

public:
	void CreateComponents();
	Component* CreateLifeNPC(std::wstring scriptName, std::wstring spriteName);
};