#include "Time.h"
#include "Entity/EntityInfo.h"
#include "Character/Character.h"
#include "Manager/GameManager.h"

Time* Time::_instance;

Time* Time::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Time();
		_instance->init();
	}
	return _instance;
}

bool Time::init()
{
	timeLabel = Label::createWithTTF("Time: 5", "fonts/Planes_ValMore.ttf", 24);
	this->addChild(timeLabel);
	return true;
}

void Time::onEnter()
{
	Label::onEnter();
	time = 5;
	this->scheduleUpdate();
}

void Time::update(float dt) {
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	if (accumulatedTime >= 1.0f && time > 0) {
		time--;
		timeLabel->setString("Time: " + std::to_string(time));
		accumulatedTime -= 1.0f;
	}
	
	if (time <= 0) {
		GameManager::getInstance()->gameOver();
		this->unscheduleUpdate();
		reset();
	}
}

void Time::reset()
{
	time = 5; 
	timeLabel->setString("Time: " + std::to_string(time));
}
