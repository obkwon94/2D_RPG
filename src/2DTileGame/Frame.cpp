#include "GameSystem.h"

#include "Texture.h"
#include "Frame.h"


Frame::Frame() :
	_frameDelay(0.0f)
{
}

Frame::~Frame()
{

}

void Frame::Init(Texture* texture, int x, int y, int width, int height, float rotate, float frameDelay)
{
	_sprite = GameSystem::GetInstance().GetSprite();
	_texture = texture;

	_width = width;
	_height = height;

	_rotate = rotate;

	// �ҽ��̹������� ��¿� ���� ������ �����Ѵ�.
	_srcTextureRect.left = x;
	_srcTextureRect.top = y;
	_srcTextureRect.right = x + _width;
	_srcTextureRect.bottom = y + _height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	_frameDelay = frameDelay;
}

void Frame::Deinit()
{

}

void Frame::Render()
{
	// ��������Ʈ ������� ��� ����� �����Ѵ�.
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_width/ 2.0f, (float)_height / 2.0f);	// �ؽ��� �ǹ� ����. �߽�����
	D3DXVECTOR2 translate = D3DXVECTOR2(_x - (float)_width / 2.0f, _y - (float)_height / 2.0f);		// �̵� ����. ���� ��ġ ����
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);		// ũ�� ����

														// ��ȯ ��� ����
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,	// ���
		NULL,	// ũ�⸦ ������ ��, ������ ���� ������� ����
		0.0f,	// ȸ�� ����
		&scaling,	// ũ�� ���� ��
		&spriteCenter,	// ȸ�� �߽�
		//0.0f,		// ȸ�� ����
		_rotate,
		&translate	// x, y ��ġ
	);

	// ������ ��� ����
	_sprite->SetTransform(&matrix);

	_sprite->Draw(_texture->GetTextureDX(), &_srcTextureRect, NULL, NULL, _textureColor);
}

void Frame::Release()
{

}

void Frame::Reset()
{

}

float Frame::GetFrameDelay()
{
	return _frameDelay;
}

void Frame::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}
