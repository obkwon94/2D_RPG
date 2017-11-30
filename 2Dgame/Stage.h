#pragma once
#include <string>
#include <list>

class Component;
class Map;

class Stage
{
private:
	std::list<Component*> _componentList;
public:
	Stage();
	~Stage();
	void Init(std::wstring name);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	//Map
private:
	Map* _map;
public:
	Map* GetMap() { return _map; }

	//NPC
private:
	int _lifeNPCcount;
	std::list<Component*> _createBaseComponentList;
	std::list<Component*> _removeComponentList;
public:
	void CreateLifeNPC(Component* component);
	void UpdateBaseComponentList();
	void UpdateRemoveComponentList();
	void CheckDestroyLifeNPC(Component* component);
	void DestroyLifeNPC(int tileX, int tileY, Component* component);
};