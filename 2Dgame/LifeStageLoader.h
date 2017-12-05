#pragma once
#include <windows.h>
#include <string>


class Component;
class Stage;

class LifeStageLoader
{
public:
	LifeStageLoader(Stage* stage);
	~LifeStageLoader();

private:
	std::wstring _name;
	Stage* _stage;
	int _lifeNPCcount;

public:
	void CreateComponents(int count);
	Component* CreateLifeNPC(LPCWSTR scriptName, LPCWSTR textureFileName);
	void SetName(LPCWSTR name);
};