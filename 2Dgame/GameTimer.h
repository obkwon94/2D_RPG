#pragma once

class GameTimer
{
private:
	double _deltaTime;
	double _secondPerCount;		//****�� ī��Ʈ �� �ð�****
	__int64 _prevCount;
public:
	GameTimer();
	~GameTimer();

	void Reset();
	void Update();
	float GetDeltaTime();
};