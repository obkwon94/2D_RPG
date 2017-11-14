#pragma once

class Component;

struct sComponentMsgParam
{
	Component* sender;
	int attackPoint;

	Component* receiver;
	std::wstring message;
};