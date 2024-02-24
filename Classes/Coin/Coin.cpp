#include "Coin.h"
#include "AnimationUtilities/AnimationUtils.h"

Coin* Coin::create(EntityInfo* info)
{
	auto newObject = new Coin();
	if (newObject != nullptr && newObject->init(info)) {
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Coin::init(EntityInfo* info)
{
	if (!Entity::init(info)) {
		return false;
	}
	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
	_model->runAction(animate);
	this->addChild(_model, 2);
    return true;
}

bool Coin::loadAnimations()
{
	Entity::loadAnimations();

	AnimationUtils::loadSpriteFrameCache("Coin/", "coin-idle");
	AnimationUtils::createAnimation("coin-idle", 1.0f);

	return true;
}
