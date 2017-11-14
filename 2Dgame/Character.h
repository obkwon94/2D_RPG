#pragma once
#include <windows.h>
#include <vector>
#include <list>
#include "Component.h"

class Sprite;


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
	bool _isMoving;
	float _moveTime;
	float _movingDuration;

	float _targetX;
	float _targetY;

	enum eDirection
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};
	eDirection _currentDirection;
public:
	void InitMove();
	void MoveStart(eDirection direction);
	virtual void UpadateMove(float deltaTime);
	virtual void Collision(std::list<Component*>& collisionList);

	//Action
protected:
	int _hp;
	int _attackPoint;

public:
	//void ReceiveMessage(std::wstring message, const sComponentMsgParam& msgParam);
	void ReceiveMessage(const sComponentMsgParam& msgParam);
	
};