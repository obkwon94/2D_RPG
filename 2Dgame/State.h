#pragma once
#include <vector>

class Character;
enum eStateType;

class State
{
public:
	State();
	~State();

protected:
	Character* _character;
	std::vector<Sprite*> _spriteList;
	eStateType _nextState;

public:
	virtual void Init(Character* character);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();
	virtual void Reset();

	virtual void Start();
	virtual void Stop();

	virtual void CreateSprite();

	void NextState(eStateType nextState);
};