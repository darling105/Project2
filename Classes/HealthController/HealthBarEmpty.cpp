#include "HealthBarEmpty.h"

HealthBarEmpty* HealthBarEmpty::_instance;

HealthBarEmpty* HealthBarEmpty::getInstance(std::string fillPath)
{
	if (_instance == nullptr)
	{
		_instance = new HealthBarEmpty();
		_instance->init(fillPath);
	}
	return _instance;
}

bool HealthBarEmpty::init(std::string fillPath)
{
	if (!Sprite::initWithFile(fillPath))
	{
		return false;
	}
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	return true;
}
