#pragma once

class GameTimer
{
private:
	double _deltaTime;
	double _secondPerCount;		//****한 카운트 당 시간****
	__int64 _prevCount;
public:
	GameTimer();
	~GameTimer();

	void Reset();
	void Update();
	float GetDeltaTime();
};