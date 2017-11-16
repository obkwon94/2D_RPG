#pragma once
#include "State.h"

class AttackState : public State
{
public:
	AttackState();
	~AttackState();

	void Init(Character* character);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Start();
	void Stop();
};