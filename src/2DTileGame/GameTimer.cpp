#include <Windows.h>
#include "GameTimer.h"


GameTimer::GameTimer() :
	_secondsPerCount(0.0), _deltaTime(-1.0),
	_currentTime(0), _prevTime(0)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);		// �ʴ� ������ ��´�.
	_secondsPerCount = 1.0 / (double)countsPerSec;		// �ʴ��� �ð��� ����Ѵ�.
}

GameTimer::~GameTimer()
{

}

float GameTimer::GetDeltaTime()
{
	return (float)_deltaTime;
}

void GameTimer::Reset()
{
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	_prevTime = currentTime;
}

void GameTimer::Update()
{
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);	// 64��Ʈ ������ �̿��ؼ� �ð� ���� �����ش�. �ð��� ���� ������ ����. ���� �ð��� ��´�.
	_currentTime = currentTime;

	_deltaTime = (_currentTime - _prevTime) * _secondsPerCount;	// ����ð� ���

	_prevTime = _currentTime;

	if (_deltaTime < 0.0)
	{
		_deltaTime = 0.0;
	}
}

