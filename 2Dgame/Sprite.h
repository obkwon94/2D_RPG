#pragma once

#include <vector>
#include <d3dx9.h>

class Frame;
class Texture;

class Sprite
{
private:
	Texture* _srcTexture;
	std::vector<Frame*> _frameList;
	int _currentFrame;
	float _frameTime;

	LPCWSTR _textureFileName;
	LPCWSTR _scriptFileName;

	int _x;
	int _y;

	float _rotate;

public:
	Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName, float rotate = 0.0f);
	~Sprite();

	void Init();
	void Init(int srcX, int srcY, int width, int height, float frameDelay);
	void DeInit();

	void Update(float deltaTime);
	void Render();

	void Release();
	void Reset();

	void SetPosition(float x, float y);

	//DirectX
private:
	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;
};