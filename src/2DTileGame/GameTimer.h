#pragma once


class GameTimer
{
private:
	double _secondsPerCount;
	double _deltaTime;

	__int64 _currentTime;
	__int64 _prevTime;

public:
	GameTimer();
	~GameTimer();

	float GetDeltaTime();

	void Reset();	// ������Ʈ �� �ѹ� ȣ��
	void Update();	// �� �����Ӹ��� ȣ��
};