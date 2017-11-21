#include <stdio.h>
#include <string>

#include "ComponentSystem.h"

#include "Map.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "GameSystem.h"
#include "GameTimer.h"

GameSystem* GameSystem::_instance = NULL;

GameSystem::GameSystem()
{
	_isFullScreen = false;
	_frameDuration = 0.0f;
}

GameSystem::~GameSystem()
{
	RELEASE_COM(_device3d);
	RELEASE_COM(_sprite);
}

GameSystem* GameSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new GameSystem();

	return _instance;
}

int GameSystem::GetClientWidth()
{
	return 1280;
}

int GameSystem::GetClientHeight()
{
	return 720;
}

LPDIRECT3DDEVICE9 GameSystem::GetDevice3d()
{
	return _device3d;
}

LPD3DXSPRITE GameSystem::GetSprite()
{
	return _sprite;
}

void GameSystem::InitInput()
{
	for (int i = 0; i < 256; i++)
	{
		_keyState[i] = eKeyState::KEY_UP;
	}
}

void GameSystem::KeyDown(unsigned int keyCode)
{
	_keyState[keyCode] = eKeyState::KEY_DOWN;
}

void GameSystem::KeyUp(unsigned int keyCode)
{
	_keyState[keyCode] = eKeyState::KEY_UP;
}

bool GameSystem::IsKeyDown(unsigned int keyCode)
{
	return (eKeyState::KEY_DOWN == _keyState[keyCode]);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		GameSystem::GetInstance()->KeyDown(wParam);
		
		if (VK_ESCAPE == wParam)
		{
			ComponentSystem::GetInstance()->RemoveAllComponents();
			DestroyWindow(hWnd);
		}
			
		return 0;

	case WM_KEYUP:
		GameSystem::GetInstance()->KeyUp(wParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);
		return 0;

		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool GameSystem::InitDirect3D()
{
	LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d)
	{
		MessageBox(0, L"Direct3DCreat Failed", L"Direct3DCreat Failed", 0);

		return false;
	}	

	
	_d3dpp;
	ZeroMemory(&_d3dpp, sizeof(_d3dpp));

	_d3dpp.BackBufferWidth = GetClientWidth();
	_d3dpp.BackBufferHeight = GetClientHeight();

	if (_isFullScreen)
	{
		_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	_d3dpp.BackBufferCount = 1;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = _hMainWnd;
	_d3dpp.Windowed = (!_isFullScreen);
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	HRESULT hr = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	DWORD behavior;

	if (FAILED(hr))
	{
		MessageBox(0, L"D3DCAPS9 Failed", L"D3DCAPS9 Failed", 0);

		return false;
	}

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0
		|| (caps.VertexShaderVersion < D3DVS_VERSION(1, 1)))
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	else
	{
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hMainWnd, behavior, &_d3dpp, &_device3d);
	if (FAILED(hr))
	{
		MessageBox(0, L"CreateDevice Failed", L"CreateDevice Failed", 0);

		return false;
	}
	
	hr = D3DXCreateSprite(_device3d, &_sprite);
	if (FAILED(hr))
	{
		MessageBox(0, L"D3DXCreateSprite Failed", L"D3DXCreateSprite Failed", 0);

		return false;
	}

	return true;
}

bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	//창의 특징 기술
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;		//윈도우 프로시저 = 윈도우에서 메세지를 받아서 각자 스타일대로 처리
	wc.cbClsExtra = 0;		//추가 메모리 슬롯 (아무도 안씀)
	wc.cbWndExtra = 0;		//추가 메모리 슬롯 (아무도 안씀)
	wc.hInstance = hInstance;		// hInstance : 현재 앱의 핸들
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);		//아이콘 셋팅
	wc.hCursor = LoadCursor(0, IDC_ARROW);		//커서 셋팅
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//배경(흰색)
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Base";		//윈도우 이름

									//등록
	if (!RegisterClass(&wc))
		return false;

	//생성
	DWORD style;
	if (_isFullScreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	_hMainWnd = CreateWindow
	(L"Base", L"Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	if (false == _isFullScreen)
	{
		RECT clientRect;
		GetClientRect(_hMainWnd, &clientRect);

		int addWidth = GetClientWidth() - clientRect.right;
		int addHeight = GetClientHeight() - clientRect.bottom;
		int finalWidth = GetClientWidth() + addWidth;
		int finalHeight = GetClientHeight() + addHeight;

		MoveWindow(_hMainWnd, 0, 0, finalWidth, finalHeight, TRUE);
	}

	//출력
	ShowWindow(_hMainWnd, nCmdShow);

	//업데이트
	UpdateWindow(_hMainWnd);

	if (false == InitDirect3D())
		return false;

	_componentList.clear();

	Map* map = new Map(L"MapData");
	_componentList.push_back(map);


	Player* player = new Player(L"player", L"player", L"player");
	_componentList.push_back(player);
	
	for (int i = 0; i < 20; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		NPC* npc = new NPC(name, L"npc", L"character_sprite2");
		_componentList.push_back(npc);
	}
	
	/*
	NPC* npc = new NPC(L"npc", L"npc", L"character_sprite2");
	_componentList.push_back(npc);
	*/
	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Monster* monster = new Monster(name, L"monster", L"monster");
		_componentList.push_back(monster);
	}

	//Monster* monster = new Monster(L"monster", L"monster", L"monster");
	//_componentList.push_back(monster);
		
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Init();
	}

	map->InitViewer(player);

	/*
	//Font
	{
	
		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0);
		_testFont = new Font(L"Arial", 35, color);

		int x = 100;
		int y = 100;

		int width = 400;
		int height = 100;

		RECT rect;
		rect.left = x;
		rect.right = x + width;
		rect.top = y;
		rect.bottom = y + height;

		_testFont->SetRect(rect);
		_testFont->SetText(L"qwerasdfzxcv");
	}
	*/
		

	return true;
}

int GameSystem::Update()
{
	//메세지 루프
	MSG msg = { 0 };

	GameTimer _gameTimer;

	_gameTimer.Reset();

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))		//윈도우 처리
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_gameTimer.Update();
			float deltaTime = _gameTimer.GetDeltaTime();
			_frameDuration += deltaTime;

			ComponentSystem::GetInstance()->UpdateMsg(deltaTime);
			
			for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
			{
				(*it)->Update(deltaTime);
			}

			float secondPerFrame = 1.0f / 60.0f;
			if (secondPerFrame <= _frameDuration)
			{
				wchar_t timeCheck[256];
				swprintf(timeCheck, L"deltaTime %f\n", _frameDuration);

				OutputDebugString(timeCheck);
				_frameDuration = 0.0f;
				
				//게임처리
				_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

				_device3d->BeginScene();

				_sprite->Begin(D3DXSPRITE_ALPHABLEND);
				
				for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
				{
					(*it)->Render();
				}

				
				//_testFont->Render();

				_sprite->End();

				_device3d->EndScene();

				ChackDeviceLost();

				_device3d->Present(NULL, NULL, NULL, NULL);
				
			}	
		}
	}
	return (int)msg.wParam;
}

void GameSystem::ChackDeviceLost()
{
	HRESULT hr = _device3d->TestCooperativeLevel();
	/*
	D3DERR_DEVICELOST: 디바이스가 로스트 상태가 되어서 현재 복구할 수 없다.
	D3DERR_DEVICENOTRESET : 디바이스를 다시 작동할 수 있다.
	D3DERR_DRIVERINTERNALERROR : 디바이스에 내부 에러가 있다. 할 수 있는 방법은 없다. (게임이 숨졌습니다)
	*/
	if (FAILED(hr))
	{
		if (D3DERR_DEVICELOST == hr)
		{
			//기다리기
			Sleep(100);

			return;
		}
		else if (D3DERR_DEVICENOTRESET == hr)
		{
			//복구
			for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
			{
				(*it)->Release();
			}

			InitDirect3D();

			hr = _device3d->Reset(&_d3dpp);
		
			for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
			{
				(*it)->Reset();
			}
		}
	}
}