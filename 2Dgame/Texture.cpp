#include "GameSystem.h"
#include "Texture.h"


Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::Init(LPCWSTR sprite)
{
	//Texture
	//���Ϸ� �̹��� ���� �ʺ� ������
	//_textureInfo;
	HRESULT hr = D3DXGetImageInfoFromFile(sprite, &_textureInfo);
	if (FAILED(hr))
	{
		MessageBox(0, L"character_sprite Info Load Fail", L"character_sprite Info Load Fail", 0);
		return;
	}
	//�ؽ��� ����
	hr = D3DXCreateTextureFromFileEx(
		GameSystem::GetInstance()->GetDevice3d(),
		sprite,
		_textureInfo.Width,
		_textureInfo.Height,
		1, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_textureInfo,
		NULL,
		&_texture);
	if (FAILED(hr))
	{
		MessageBox(0, L"Create Texture Fail", L"Create Texture Fail", 0);
		return;
	}
}

void Texture::DeInit()
{

}

void Texture::Release()
{

}


IDirect3DTexture9* Texture::GetTextureDX()
{
	return _texture;
}