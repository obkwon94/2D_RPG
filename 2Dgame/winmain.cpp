#include <windows.h>

#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)		//() �ڿ��� �ǹ�
{
	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);
	
	GameSystem::GetInstance()->Update();
}
