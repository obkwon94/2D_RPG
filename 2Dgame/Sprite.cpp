#include <fstream>
#include <reader.h>

#include "ResourceManager.h"
#include "GameSystem.h"
#include "Frame.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName) :	_currentFrame(0), _frameTime(0), _srcTexture(NULL),  _textureFileName(textureFileName), _scriptFileName(scriptFileName)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init()
{
	_device3d = GameSystem::GetInstance()->GetDevice3d();
	_sprite = GameSystem::GetInstance()->GetSprite();

	
	_srcTexture = new Texture();
	_srcTexture->Init(_textureFileName);
	

	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);

	//json test
	{
		//텍스트 정보로 파일읽기
		//텍스트 정보를 파싱
		//파싱된 정보를 토큰 -> 의미있는 게임 정보 변환
		//변환된 정보를 이용해서 Frame 생성
		std::vector<std::string> scriptTextList = ResourceManager::GetInstance()->LoadScript(_scriptFileName);

		for (int i = 0; i < scriptTextList.size(); i++)
		{
			std::string record = scriptTextList[i];

			Json::Value root;
			Json::Reader reader;
			bool isSuccess = reader.parse(record, root);
			if (isSuccess)
			{
				std::string texture = root["texture"].asString();
				int x = root["x"].asInt();
				int y = root["y"].asInt();
				int width = root["width"].asInt();
				int height = root["height"].asInt();
				double framedelay = root["framedelay"].asDouble();

				Frame* frame = new Frame();
				frame->Init(_srcTexture, x, y, width, height, framedelay);
				_frameList.push_back(frame);
			}
		}
	}

	_currentFrame = 0;
	_frameTime = 0;
}

void Sprite::Init(int srcX, int srcY, int width, int height, float frameDelay)
{
	_device3d = GameSystem::GetInstance()->GetDevice3d();
	_sprite = GameSystem::GetInstance()->GetSprite();
	
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);
	
	{
		Frame* frame = new Frame();
		frame->Init(_srcTexture, srcX, srcY, width, height, frameDelay);
		_frameList.push_back(frame);
	}

	_currentFrame = 0;
	_frameTime = 0;
}

void Sprite::DeInit()
{
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = (*it);
		frame->DeInit();
		delete frame;
	}
	_frameList.clear();

	_srcTexture->DeInit();
	delete _srcTexture;
	_srcTexture = NULL;
}

void Sprite::Update(float deltaTime)
{
	
	_frameTime += deltaTime;
	if (_frameList[_currentFrame]->GetFrameDelay() <= _frameTime)
	{
		_frameTime = 0.0f;
		_currentFrame = (_currentFrame + 1) % _frameList.size();
	}
}

void Sprite::Render()
{
	if (_currentFrame < _frameList.size())
	{
		_frameList[_currentFrame]->SetPosition(_x, _y);
		_frameList[_currentFrame]->Rander();
	}
}

void Sprite::Release()
{
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = (*it);
		frame->Release();
	}

	_srcTexture->Release();
}

void Sprite::Reset()
{
	Init();
	
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = (*it);
		frame->Reset();
	}
}

void Sprite::SetPosition(float x, float y)
{
	_y = y;
	_x = x;
}