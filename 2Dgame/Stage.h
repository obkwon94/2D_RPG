#pragma once
#include <list>

class Component;
class Map;
class NPC;
class LifeStageLoader;

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
	std::list<Component*> _removeComponentList;
	std::list<Component*> _createBaseComponentList;
	LifeStageLoader* _lifeStageLoader;

public:
	Map* GetMap() { return _map; }

public:
	void CreateLifeNPC(Component* component);

	void DestroyNPC(int tileX, int tileY, Component* tileCharacter);
	void CheckDestroyNPC(Component* component);
	void UpdateRemoveComponentList();
	void UpdateBaseComponentList();

	void AddStageComponent(Component* component);
};