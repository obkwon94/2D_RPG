#pragma once

#include "State.h"

class Character;

class MoveState : public State
{
public:
	MoveState();
	~MoveState();

private:
	//bool _isMoving;
	float _movingDuration;
	//Character* _character;

public:

	void Init(Character* character);
	void Update(float deltaTime);
	//void UpdateMove(float deltaTime);

	//bool isMoving();

	//void SetMoving(bool isMoving);
	//float GetMovingDuration();
	
	void Start();
	void Stop();
	
};
