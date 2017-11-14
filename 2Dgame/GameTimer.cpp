#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer():
	_secondPerCount(0.0), _deltaTime(-1.0), _prevCount(0)	//�Լ��� ������ ������ �ʱ�ȭ (�ȿ��� �ʱ�ȭ�ϴ� �� ���� ������)
{
	__int64 countPerSecond;		//1�� �� ī��Ʈ
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSecond);
	_secondPerCount = 1.0 / (double)countPerSecond;
}
GameTimer::~GameTimer()
{

}

void GameTimer::Reset()
{
	__int64 currentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);
	_prevCount = currentCount;
}

void GameTimer::Update()
{
	__int64 currentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);
	_deltaTime = (currentCount - _prevCount) * _secondPerCount;
	_prevCount = currentCount;
}

float GameTimer::GetDeltaTime()
{
	return (float)_deltaTime;
}