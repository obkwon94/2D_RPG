#pragma once
#include <windows.h>
#include <vector>
#include <list>
#include <string>
#include <map>
#include "Component.h"

class Sprite;
class State;
class Font;
class TileCell;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
	ET_ATTACK,
	ET_DEFENCE,
	ET_RECOVERY,
	ET_DEAD,
	ET_PATHFINDING,
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
	std::vector<Sprite*> _spriteList;
	std::wstring _textureFilename;
	std::wstring _scriptFilename;

protected:
	float _x;
	float _y;
	
public:
	Character(std::wstring name, std::wstring scriptName, std::wstring textureFileName);
	~Character();

	void Init();
	void Init(int tileX, int tileY);
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
	bool _isMoving;
	float _moveTime;
	State* _state;

	float _targetX;
	float _targetY;

	
	eDirection _currentDirection;
public:
	void InitMove();
	void InitStage();
	void MoveStart(int newTileX, int newTileY);
	void MoveStop();
	//void UpadateMove(float deltaTime);
	void Moving(float deltaTime);

	bool IsMoving() { return _isMoving; }
	float GetMoveTime() { return _moveTime; }

	eDirection GetDirection() { return _currentDirection; }
	virtual Component* Collision(std::list<Component*>& collisionList);

	void InitTilePosition(int tileX, int tileY);

	//Message
public:
	void ReceiveMessage(const sComponentMsgParam& msgParam);

	//Common
public:
	void IncreaseHP(int increaseHP);
	void DecreaseHP(int decreaseHP);
	
	//State
private:
	std::map<eStateType, State*> _stateMap;

public:
	void ChangeState(eStateType stateType);
	void ReplaceState(eStateType changeType, State* replaceState);

	//Action
protected:
	int _hp;

	//Attack
protected:
	int _attackPoint;
	Component* _target;

	float _attackCooltimeDuration;
	float _attackSpeed;

public:
	int GetAttackPoint() { return _attackPoint; }
	Component* GetTarget() { return _target; }
	void ResetTarget() { _target = NULL; }
	void SetTarget(Component* target) { _target = target; }

	void UpdateAttackCooltime(float deltaTime);
	void ResetAttackCooltime();
	bool IsAttackCooltime();
	
	//Defence
protected:
	int _damage;

public:
	int GetDamage() { return _damage; }

	//Recovery
protected:
	int _maxHP;
	int _recovery;

	float _recoveryCooltimeDuration;
	float _recoveryCooltime;

public:
	bool IsHpFull();

	//UI
protected:
	Font* _font;

public:
	void UpdateText();

	//Pathfinding
protected:
	TileCell* _targetTileCell;

public:
	TileCell* GetTargetTileCell() { return _targetTileCell; }
	void SetTargetTileCell(TileCell* tileCell);
};