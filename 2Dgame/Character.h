#pragma once
#include <windows.h>
#include <vector>
#include <list>
#include "Component.h"

class Sprite;
class MoveState;

enum eDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

class Character : public Component
{
private:
	//Sprite* _sprite;
	std::vector<Sprite*> _spriteList;
	std::wstring _textureFileName;
	std::wstring _scriptName;

protected:
	float _x;
	float _y;
	
public:
	Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~Character();

	void Init();
	void DeInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	//transform
public:
	virtual void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);

	//AI
public:
	virtual void UpdateAI(float deltaTime);

	//move
protected:
	/*
	bool _isMoving;
	float _movingDuration;
	*/
	float _moveTime;
	MoveState* _state;

	float _targetX;
	float _targetY;

	
	eDirection _currentDirection;
public:
	void InitMove();
	void MoveStart(int newTileX, int newTileY);
	void UpadateMove(float deltaTime);

	eDirection GetDirection() { return _currentDirection; }
	virtual void Collision(std::list<Component*>& collisionList);

	//Action
protected:
	int _hp;
	int _attackPoint;

public:
	void ReceiveMessage(const sComponentMsgParam& msgParam);
	
};