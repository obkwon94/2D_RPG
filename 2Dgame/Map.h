#pragma once
#include <windows.h>
#include <vector>
#include "TileCell.h"
#include "Component.h"

class Sprite;
class TileCell;

class Map : public Component
{
private:
	std::vector< std::vector<TileCell*> > _tileMap;
	int _width;
	int _height;

	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;

	int _tileSize;
		
	Component* _viewer;

	std::vector<Sprite*> _spriteList;

public:
	Map(LPCWSTR name);
	~Map();
	void Init();
	void DeInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Scroll(float deltaX, float deltaY);

	int GetPositionX(int tileX, int tileY);
	int GetPositionY(int tileX, int tileY);

	int GetWidth();
	int GetHeight();

	void SetTileComponent(int tileX, int tileY, Component* component, bool isRender);
	void ResetTileComponent(int tileX, int tileY, Component* component);
	std::list<Component*> GetTileComponentList(int tileX, int tileY);

	bool CanMoveTileMap(int tileX, int tileY);
	bool GetTileCollisionList(int tileX, int tileY, std::list<Component*>& collisionList);
	

	void InitViewer(Component* viewer);
};