#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include "ComponentMessage.h"
#include "Component.h"

class ComponentSystem
{
	// Singleton
private:
	static ComponentSystem* _instance;

public:
	static ComponentSystem& GetInstance();

private:
	ComponentSystem();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.
public:
	~ComponentSystem();

	void Update(float deltaTime);

	// Component Map
private:
	std::map<std::wstring, Component*> _componentMap;

public:
	void AddComponent(std::wstring name , Component* com);
	void RemoveAllComponents();
	void RemoveComponent(Component* component);

	Component* FindComponent(std::wstring name);
	Component* FindComponentInRange(Component* mapComp, Component* chaser, int range, std::vector<eComponentType> compareTypeList);

	// Message
private:
	std::queue<sComponentMsgParam> _msgQueue;

public:
	void SendMsg(const sComponentMsgParam& msgParam);
	void ProcessMessageQueue();
	void ClearMessageQueue();
};

