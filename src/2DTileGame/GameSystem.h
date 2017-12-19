#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <list>

#include "GameTimer.h"

#define RELEASE_COM(x) { if(x){x->Release(); x=NULL;}}

class Component;
class NPC;
class Stage;

class GameSystem
{
	// Singleton
private:
	static GameSystem* _instance;

public:
	static GameSystem& GetInstance();

private:
	GameSystem();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.

public:
	~GameSystem();

	// System
private:
	HWND _hMainWnd;

	int _clientWidth;
	int _clientHeight;

public:
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();

	int GetClientWidth();
	int GetClientHeight();

private:
	bool InitMainWindow(HINSTANCE hInstance, int nCmdShow);

	// Direct3D
private:
	LPDIRECT3D9 _direct3d;
	D3DPRESENT_PARAMETERS _d3dpp;
	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;

	bool _isFullScreen;

public:
	bool InitDirect3D();
	void CheckDeviceLost();

	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSprite();

	// Input
public:
	enum eKeyState
	{
		KEY_DOWN,
		KEY_UP
	};

private:
	eKeyState _keyState[256];

	bool _isMouseDown;
	int _mouseX;
	int _mouseY;

public:
	void InitInput();

	void MouseDown(int mouseX, int mouseY);
	void MouseUp();
	bool IsMouseDown() { return _isMouseDown; }
	int GetMouseX() { return _mouseX; }
	int GetMouseY() { return _mouseY; }

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);
	bool IsKeyDown(unsigned int keyCode);




	// Game
private:
	GameTimer _gameTimer;
	float _frameTime;


	// Component
private:
	Stage* _stage;

public:
	Stage* GetStage() { return _stage; }
};
