#include <stdio.h>
#include "Component.h"
#include "ComponentSystem.h"
#include "map.h"

ComponentSystem* ComponentSystem::_instance = NULL;

ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
}

ComponentSystem::~ComponentSystem()
{

}

ComponentSystem* ComponentSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new ComponentSystem();

	return _instance;
}



void ComponentSystem::AddComponent(std::wstring name, Component* com)
{
	if (NULL != com)
	{
		std::map<std::wstring, Component*>::iterator it = _componentMap.find(name);
		if (it == _componentMap.end())
		{
			_componentMap[name] = com;
		}
	}
}

void ComponentSystem::RemoveAllComponents()
{
	for (std::map<std::wstring, Component*>::iterator it = _componentMap.begin(); it != _componentMap.end(); it++)
	{
		delete it->second;
	}
	_componentMap.clear();
}

Component* ComponentSystem::FindComponent(std::wstring name)
{
	std::map<std::wstring, Component*>::iterator it = _componentMap.find(name);
	if (it != _componentMap.end())
	{
		return it->second;
	}
	return 0;
}

Component* ComponentSystem::FindComponentInRange(Component* chaser, int range, std::vector<eComponentType> compareTypeList)
{
	Map* map = (Map*)FindComponent(L"MapData");

	int minTileX = chaser->GetTileX() - range;
	int maxTileX = chaser->GetTileX() + range;
	int minTileY = chaser->GetTileY() - range;
	int maxTileY = chaser->GetTileY() + range;

	if (minTileX < 0)
		minTileX = 0;
	if (map->GetWidth() <= maxTileX)
		maxTileX = map->GetWidth() - 1;
	if (minTileY < 0)
		minTileX = 0;
	if (map->GetHeight() <= maxTileY)
		maxTileY = map->GetHeight() - 1;

	//Component* findEnemy = NULL;

	//탐색거리에 적이 있는 지 확인
	for (int y = minTileY; y <= maxTileY; y++)
	{
		for (int x = minTileX; x <= maxTileX; x++)
		{
			std::list<Component*> componentList;
			if (false == map->GetTileCollisionList(x, y, componentList))
			{
				for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
				{
					Component* component = (*it);
					if (true == component->IsLive())
					{
						for (int i = 0; i < compareTypeList.size(); i++)
						{
							if (compareTypeList[i] == component->GetType())
							{
								return component;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

void ComponentSystem::UpdateMsg(float deltaTime)
{
	ProcessMsgQueue();
}

void ComponentSystem::SendMsg(const sComponentMsgParam& msgParam)
{
	_msgQueue.push(msgParam);
}

void ComponentSystem::ProcessMsgQueue()
{
	while (0 < _msgQueue.size())
	{
		sComponentMsgParam msgParam = _msgQueue.front();
		_msgQueue.pop();
		msgParam.receiver->ReceiveMessage(msgParam);
	}
}