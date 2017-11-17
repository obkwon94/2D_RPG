#pragma once
#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include "Component.h"

class Sprite;
//class MoveState;
//class IdleState;
class State;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
	ET_ATTACK,
	ET_DEFENCE,
	ET_DEAD,
	ET_NONE
};

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
	std::wstring _textureFilename;
	std::wstring _scriptFilename;

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

	float GetX() { return _x; }
	float GetY() { return _y; }

	std::wstring GetTextureFilename() { return _textureFilename; }
	std::wstring GetScriptFilename() { return _scriptFilename; }

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
	
	float _movingDuration;
	*/
	bool _isMoving;
	float _moveTime;
	State* _state;

	float _targetX;
	float _targetY;

	
	eDirection _currentDirection;
public:
	void InitMove();
	void MoveStart(int newTileX, int newTileY);
	void MoveStop();
	//void UpadateMove(float deltaTime);
	void Moving(float deltaTime);

	bool IsMoving() { return _isMoving; }
	float GetMoveTime() { return _moveTime; }

	eDirection GetDirection() { return _currentDirection; }
	virtual Component* Collision(std::list<Component*>& collisionList);

	//Message
public:
	void ReceiveMessage(const sComponentMsgParam& msgParam);

	//Common
public:
	void DecreaseHP(int decreaseHP);
	
	//State
private:
	std::map<eStateType, State*> _stateMap;

public:
	void ChangeState(eStateType stateType);


	//Action
protected:
	int _hp;

	//Attack
protected:
	int _attackPoint;
	Component* _target;

public:
	int GetAttackPoint() { return _attackPoint; }
	Component* GetTarget() { return _target; }
	void ResetTarget() { _target = NULL; }
	void SetTarget(Component* target) { _target = target; }

	//Defence
protected:
	int _attackedPoint;

public:
	int GetAttackedPoint() { return _attackedPoint; }
};