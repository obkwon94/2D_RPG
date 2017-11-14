#pragma once
#include <d3dx9.h>

class Texture
{
private:
	D3DXIMAGE_INFO _textureInfo;
	IDirect3DTexture9* _texture;

public:
	Texture();
	~Texture();

	void Init(LPCWSTR sprite);
	void DeInit();
	void Release();

	IDirect3DTexture9* GetTextureDX();
};