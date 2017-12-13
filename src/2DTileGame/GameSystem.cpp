#include <string>
#include "ComponentSystem.h"
#include "Stage.h"
#include "GameSystem.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

GameSystem* GameSystem::_instance = 0;

// Singleton
GameSystem& GameSystem::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new GameSystem();
	}
	return *_instance;
}

GameSystem::GameSystem()
{
	_clientWidth = 1280;
	_clientHeight = 800;

	_isFullScreen = false;

	_frameTime = 0.0f;

	//_npcCount = 0;
}

GameSystem::~GameSystem()
{
	delete _stage;

	RELEASE_COM(_device3d);
	RELEASE_COM(_direct3d);
}

bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	if (false == InitMainWindow(hInstance, nCmdShow))
	{
		MessageBox(0, L"Failed InitMainWindow", 0, 0);
		return false;
	}

	if (false == InitDirect3D())
	{
		MessageBox(0, L"Failed InitDirect3D", 0, 0);
		return false;
	}

	_stage = new Stage();
	_stage->Init(L"Map1");

	return true;
}

int GameSystem::Update()
{
	_gameTimer.Reset();

	// �޽��� ����
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_gameTimer.Update();
			float deltaTime = _gameTimer.GetDeltaTime();
			_frameTime += deltaTime;

			ComponentSystem::GetInstance().Update(deltaTime);
			
			_stage->Update(deltaTime);
			
			float minFrameTime = 1.0f / 60.0f;
			if (minFrameTime <= _frameTime)
			{	
				/*
				wchar_t timeTest[256];
				swprintf(timeTest, L"delta time %f\n", _frameTime);
				OutputDebugString(timeTest);
				*/
				_frameTime = 0.0f;

				_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0);

				_device3d->BeginScene();

				// ��������Ʈ�� ȭ�鿡 �׸���.
				_sprite->Begin(D3DXSPRITE_ALPHABLEND);		// png ������ �����Ѵ�.
				
				_stage->Render();
				
				_sprite->End();

				_device3d->EndScene();

				CheckDeviceLost();

				_device3d->Present(NULL, NULL, NULL, NULL);
			}

			// Stage ��ü �׽�Ʈ
			{
				if (IsKeyDown(VK_F1))
				{
					ComponentSystem::GetInstance().ClearMessageQueue();
					delete _stage;
					_stage = new Stage();
					_stage->Init(L"Map2");
				}
				if (IsKeyDown(VK_F2))
				{
					ComponentSystem::GetInstance().ClearMessageQueue();
					delete _stage;
					_stage = new Stage();
					_stage->Init(L"Map3");
				}
				if (IsKeyDown(VK_F3))
				{
					ComponentSystem::GetInstance().ClearMessageQueue();
					delete _stage;
					_stage = new Stage();
					_stage->Init(L"Map4");
				}
			}
		}
	}

	return (int)msg.wParam;
}

int GameSystem::GetClientWidth()
{
	return _clientWidth;
}

int GameSystem::GetClientHeight()
{
	return _clientHeight;
}

bool GameSystem::InitMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	// â�� Ư�� ���
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// Ŭ���̾�Ʈ ������ ��� ��
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BaseWndClass";

	// â�� Ư���� ����ϱ� ���� ����Ѵ�.
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"Failed Register WndClass", 0, 0);
		return false;
	}

	// �����츦 �����Ѵ�.
	DWORD style;
	if (_isFullScreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPED;
	}

	_hMainWnd = CreateWindow(
		L"BaseWndClass",
		L"2D TileMap Game",
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		hInstance,
		0
	);

	if (0 == _hMainWnd)
	{
		MessageBox(0, L"Fail CreateWindow", 0, 0);
		return false;
	}

	// â��� �� �� Ŭ���̾�Ʈ ũ�� ����
	if (false == _isFullScreen)
	{
		// ������ ũ�⸦ ������, ������ ������ ���� ���� ������ �ǵ��� �Ѵ�.
		RECT clientRect;
		GetClientRect(_hMainWnd, &clientRect);
		MoveWindow(_hMainWnd,
			0,
			0,
			_clientWidth + (_clientWidth - clientRect.right),
			_clientHeight + (_clientHeight - clientRect.bottom),
			TRUE	// �����츦 �ٽ� �׸���.
		);
	}

	ShowWindow(_hMainWnd, nCmdShow);
	UpdateWindow(_hMainWnd);

	return true;
}

bool GameSystem::InitDirect3D()
{
	_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == _direct3d)
		return false;

	ZeroMemory(&_d3dpp, sizeof(_d3dpp));
	_d3dpp.BackBufferWidth = _clientWidth;
	_d3dpp.BackBufferHeight = _clientHeight;
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
	_d3dpp.hDeviceWindow - _hMainWnd;
	_d3dpp.Windowed = (!_isFullScreen);
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	DWORD behavior;
	HRESULT hr = _direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
		return false;

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		(caps.VertexShaderVersion < D3DVS_VERSION(1, 1)) )
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	hr = _direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hMainWnd,
		behavior,
		&_d3dpp,
		&_device3d);
	if (FAILED(hr))
		return false;

	hr = D3DXCreateSprite(_device3d, &_sprite);
	
	return true;
}

void GameSystem::CheckDeviceLost()
{
	HRESULT hr = _device3d->TestCooperativeLevel();
	
	if (FAILED(hr))	// ��ȿ�� ���°� �ƴ϶��
	{
		if (D3DERR_DEVICELOST == hr)
		{
			Sleep(100);
			return;
		}
		else if (D3DERR_DEVICENOTRESET == hr)
		{
			_stage->Release();

			InitDirect3D();
			hr = _device3d->Reset(&_d3dpp);

			_stage->Reset();
		}
	}
}

LPDIRECT3DDEVICE9 GameSystem::GetDevice()
{
	return _device3d;
}

LPD3DXSPRITE GameSystem::GetSprite()
{
	return _sprite;
}

void GameSystem::InitInput()
{

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
	case WM_LBUTTONDOWN:
		return 0;

	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
		{
			ComponentSystem::GetInstance().RemoveAllComponents();
			DestroyWindow(hWnd);
		}
		GameSystem::GetInstance().KeyDown(wParam);
		return 0;

	case WM_KEYUP:
		GameSystem::GetInstance().KeyUp(wParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);		// WM_QUIT �޽����� â�� ����. WM_QUIT �޽����� ť�� �ִ´�.
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}