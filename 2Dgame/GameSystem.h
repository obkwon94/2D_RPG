#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <list>
#include <string>
#include <vector>

#define RELEASE_COM(x){if(x) {x->Release(); x = NULL;}}

class Component;
class Font;
class Character;
class Map;

class Stage;

class GameSystem
{
	//Singleton
private:
	static GameSystem* _instance;

public:
	static GameSystem* GetInstance();

private:
	GameSystem();
public:
	~GameSystem();

	//GameSystem
public:
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();

	int GetClientWidth();
	int GetClientHeight();
	LPDIRECT3DDEVICE9 GetDevice3d();
	LPD3DXSPRITE GetSprite();
	

	//Direct3D
private:
	HWND _hMainWnd;

	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;
	D3DPRESENT_PARAMETERS _d3dpp;


	bool _isFullScreen;

	float _frameDuration;

public:
	bool InitDirect3D();
	void ChackDeviceLost();

	//Component
private:
	Stage* _stage;

public:
	Stage* GetStage() { return _stage; }
	//Input
public:
	enum eKeyState
	{
		KEY_DOWN,
		KEY_UP
	};

private:
	eKeyState _keyState[256];

public:
	void InitInput();
	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);
	bool IsKeyDown(unsigned int keyCode);

	//Font Test
private:
	//ID3DXFont* _dxTestFont;
	Font* _testFont;
};