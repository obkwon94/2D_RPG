#include <windows.h>

#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)		//() 자원을 의미
{
	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);
	
	GameSystem::GetInstance()->Update();
}
