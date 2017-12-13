#include "GameSystem.h"

#include "Texture.h"


Texture::Texture()
{
	_texture = NULL;
}

Texture::~Texture()
{

}

void Texture::Init(LPCWSTR fileName)
{
	// ���Ϸ� ���� �̹����� ���� ���̸� ��´�.
	//D3DXIMAGE_INFO texInfo;	// ��� ����ȭ
	HRESULT hr = D3DXGetImageInfoFromFile(fileName, &_texInfo);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed D3DXGetImageInfoFromFile", 0, 0);
		return;
	}

	// ���Ϸκ��� �ؽ��ĸ� �ε��� �����Ѵ�.
	hr = D3DXCreateTextureFromFileEx(GameSystem::GetInstance().GetDevice(), fileName,
		_texInfo.Width, _texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		//D3DCOLOR_ARGB(255, 44, 133, 133),
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo,
		NULL,
		&_texture
	);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed D3DXCreateTextureFromFileEx", 0, 0);
		return;
	}
}

void Texture::Deinit()
{
	RELEASE_COM(_texture);
}

void Texture::Release()
{
	RELEASE_COM(_texture);
}

IDirect3DTexture9* Texture::GetTextureDX()
{
	return _texture;
}