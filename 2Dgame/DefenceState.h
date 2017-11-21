#pragma once
#include "State.h"

class Character;

class DefenceState : public State
{
public:
	DefenceState();
	~DefenceState();

	void Init(Character* character);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Start();
	void Stop();
};