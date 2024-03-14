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
	timeLabel = Label::createWithTTF("Time: 500", "fonts/Planes_ValMore.ttf", 24);
	this->addChild(timeLabel);
	return true;
}

void Time::onEnter()
{
	Label::onEnter();
	time = 500;
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
		EntityInfo info("character");
		auto character = Character::getInstance(&info);
		auto _character = character->getCharacter(0);
		_character->getPhysicsBody()->setVelocity(Vec2::ZERO);
		_character->unscheduleUpdate();
		reset();
	}
}

void Time::reset()
{
	time = 500; 
	timeLabel->setString("Time: " + std::to_string(time));
}
