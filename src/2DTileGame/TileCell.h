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

	float _distanceWeight;		//고정된 값, 맵 로딩할 때 세팅
	float _distanceFromStart;	//계산된 값을 저장하기 위한 변수

	float _heuristic;

public:
	void InitPathfinding();
	bool IsPathfindingMark() { return _isPathfindingMark; }
	void PathFinded() { _isPathfindingMark = true; }

	float GetDistanceWeight() { return _distanceWeight; }
	float GetDistanceFromStart() { return _distanceFromStart; }
	void SetDistanceFromStart(float distance) { _distanceFromStart = distance; }

	TileCell* GetPrevPathfindingCell() { return _prevPathfindingCell;  }
	void SetPrevPathfindingCell(TileCell* tileCell) { _prevPathfindingCell = tileCell;  }

	float GetHeuristic() { return _heuristic; }
	void SetHeuristic(float heuristic) { _heuristic = heuristic; }
};
