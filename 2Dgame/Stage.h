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
public:
	void CreateLifeNPC(int tileX, int tileY);
	void DestroyLifeNPC(int tileX, int tileY, Component* tileCharacter);
};