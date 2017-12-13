#pragma once

#include <list>

class Component;

class TileCell
{
private:
	float _posX;
	float _posY;

	int _tileX;
	int _tileY;

	std::list<Component*> _componentList;
	std::list<Component*> _renderList;


public:
	TileCell(int tileX, int tileY);
	~TileCell();

	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void SetPosition(float posX, float posY);
	void MoveDeltaPosition(float deltaX, float deltaY);
	float GetPositionX();
	float GetPositionY();

	void AddComponent(Component* component, bool isRender);
	void RemoveComponent(Component* component);
	std::list<Component*> GetComponentList() { return _componentList;  }

	bool CanMove();
	bool GetCollisionList(std::list<Component*>& collisionList);

	int GetTileX() { return _tileX;  }
	int GetTileY() { return _tileY; }

	// Pathfinding
private:
	bool _isPathfindingMark;
	TileCell* _prevPathfindingCell;

public:
	void InitPathfinding();
	bool IsPathfindingMark() { return _isPathfindingMark; }
	void PathFinded() { _isPathfindingMark = true; }

	TileCell* GetPrevPathfindingCell() { return _prevPathfindingCell;  }
	void SetPrevPathfindingCell(TileCell* tileCell) { _prevPathfindingCell = tileCell;  }
};
