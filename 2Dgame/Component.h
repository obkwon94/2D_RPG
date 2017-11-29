#pragma once
#include <windows.h>
#include <string>
#include "ComponentMessage.h"

enum eComponentType
{
	CT_PLAYER,
	CT_MONSTER,
	CT_NPC,
	CT_TILE_OBJECT,
	CT_ITEM,
	CT_NONE
};

class Component
{
protected:
	eComponentType _type;
	std::wstring _name;
	bool _canMove;

	int _tileX;
	int _tileY;

	float _moveDistancePerTimeX;
	float _moveDistancePerTimeY;

public:
	Component() 
	{
		_canMove = false;
	}

	Component(std::wstring name);
	virtual ~Component();

	virtual void Init() = 0;
	virtual void DeInit() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;

	virtual void SetPosition(float posX, float posY) {}
	virtual void MoveDeltaPosition(float deltaX, float deltaY) {}

	bool CanMove() { return _canMove; }
	void SetCanMove(bool canMove) { _canMove = canMove; }

	int GetTileX() { return _tileX; }
	int GetTileY() { return _tileY; }

	float GetMoveDeltaX() { return _moveDistancePerTimeX; }
	float GetMoveDeltaY() { return _moveDistancePerTimeY; }

	eComponentType GetType() { return _type; }

	//Message
public:
	virtual void ReceiveMessage(const sComponentMsgParam& msgParam);

	//Action
protected:
	bool _isLive;

public:
	bool IsLive() { return _isLive; }
	void SetLive(bool isLive) { _isLive = isLive; }


	//Name

public:
	std::wstring GetName(){	return _name; }
}; 