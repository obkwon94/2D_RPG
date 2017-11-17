#include "Sprite.h"
#include "Character.h"
#include "State.h"

State::State()
{
}

State::~State()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DeInit();
		delete _spriteList[i];
	}
	_spriteList.clear();
}

void State::Init(Character* character)
{
	_character = character;

	CreateSprite();
	/*
	_spriteList.clear();

	WCHAR textrureFilename[256];
	wsprintf(textrureFilename, L"%s.png", _character->GetTextureFilename().c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s_left.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_right.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_up.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_down.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	*/
}

void State::Update(float deltaTime)
{
	_spriteList[(int)_character->GetDirection()]->Update(deltaTime);
}

void State::Render()
{
	_spriteList[(int)_character->GetDirection()]->SetPosition(_character->GetX(), _character->GetY());
	_spriteList[(int)_character->GetDirection()]->Render();
}

void State::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
}

void State::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
}

void State::Start()
{
}

void State::Stop()
{
}

void State::CreateSprite()
{
	_spriteList.clear();

	WCHAR textrureFilename[256];
	wsprintf(textrureFilename, L"%s.png", _character->GetTextureFilename().c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s_left.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_right.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_up.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_down.json", _character->GetScriptFilename().c_str());
		Sprite* sprite = new Sprite(textrureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
}