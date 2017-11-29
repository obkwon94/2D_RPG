#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "Component.h"
#include "ComponentMessage.h"

class Component;

class ComponentSystem
{
private:
	ComponentSystem();

public:
	~ComponentSystem();



	//Singleton
private:
	static ComponentSystem* _instance;

public:
	static ComponentSystem* GetInstance();



	//ComponentMap
private:
	std::map<std::wstring, Component*> _componentMap;

public:
	void AddComponent(std::wstring name, Component* com);
	void RemoveAllComponents();

	void RemoveComponent(Component* tileCharacter);
	Component* FindComponent(std::wstring name);

	Component* FindComponentInRange(Component* mapComp, Component* chaser, int range, std::vector<eComponentType> compareTypeList);

	//Message
private:
	std::queue<sComponentMsgParam> _msgQueue;

public:
	void SendMsg(const sComponentMsgParam& msgParam);
	void ProcessMsgQueue();
	void UpdateMsg(float deltaTime);
	void ClearMessageQueue();

	//Name


public:
	std::wstring GetName();
};