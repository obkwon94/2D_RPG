#pragma once
#include <Windows.h>
#include "Component.h"

class Sprite;

class TileObject : public Component
{
private:
	Sprite* _sprite;

	float _posX;
	float _posY;

public:
	TileObject(LPCWSTR name, Sprite* sprite);
	~TileObject();

	void Init() ;
	void DeInit() ;
	void Update(float deltaTime) ;
	void Render();
	void Release() ;
	void Reset() ;

	void SetPosition(float posX, float posY);
	void MoveDeltaPosition(float deltaX, float deltaY);
};

