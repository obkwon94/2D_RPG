#pragma once
#include <string>
#include <map>
#include <list>

class Component;
class Map;
class StageLoader;

class Stage
{
public:
	Stage();
	~Stage();

	void Init(std::wstring mapName);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

private:
	std::list<Component*> _componentList;
	Map* _map;

public:
	Map* GetMap() { return _map; }
	void SetMap(Map* map) {	_map = map;	}


	//LifeGame
private:
	std::list<Component*> _removeComponentList;
	std::list<Component*> _createBaseComponentList;

public:
	void CreateLifeNPC(Component* component);
	void DestroyNPC(int tileX, int tileY, Component* tileCharacter);
	void CheckDestroyNPC(Component* component);
	void UpdateBaseComponentList();
	void UpdateRemoveComponentList();
	
	//Part
private:
	std::map<std::wstring, StageLoader*> _stageLoader;

public:
	void AddStageComponent(Component* component);
};