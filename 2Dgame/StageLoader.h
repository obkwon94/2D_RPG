#pragma once
#include <string>

class Component;
class Stage;

class StageLoader
{
public:
	StageLoader(Stage* stage);
	~StageLoader();

protected:
	std::wstring _name;
	Stage* _stage;
	//int _lifeNPCcount;

public:
	/*
	void CreateComponents(int count);
	Component* CreateLifeNPC(LPCWSTR scriptName, LPCWSTR textureFileName);
	void SetName(LPCWSTR name);
	*/
	virtual void CreateComponents(std::wstring mapName);
	virtual Component* CreateLifeNPC(std::wstring scriptName, std::wstring textureFileName);
	virtual void SetName(std::wstring name, int id);
};