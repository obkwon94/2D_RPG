#pragma once
#include <d3dx9.h>

class Texture;

class Frame
{
private:
	int _width;
	int _height;
	float _frameDelay;

	float _x;
	float _y;


	Texture* _texture;
public:
	Frame();
	~Frame();

	void Init(Texture* texture, int x, int y, int width, int height, float frameDelay);
	void DeInit();
	void Rander();
	void Release();
	void Reset();
	float GetFrameDelay();
	//DirectX
public:
	LPD3DXSPRITE _sprite;

	RECT _srcTextureRect;
	D3DCOLOR _textureColor;

	void SetPosition(float x, float y);

};