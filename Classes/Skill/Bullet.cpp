#include "Bullet.h"
#include "DefineBitmask.h"
#include "AnimationUtilities/AnimationUtils.h"

Bullet* Bullet::create(EntityInfo* info)
{
	auto newObject = new Bullet();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Bullet::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		return false;
	}
	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName);
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + " (1)");
	_model->runAction(animate);
	this->addChild(_model, 2);
	auto bodyBullet = PhysicsBody::createCircle(_model->getContentSize().height / 4, PhysicsMaterial(1, 0, 1));
	bodyBullet->setContactTestBitmask(DefineBitmask::BULLET);
	bodyBullet->setCollisionBitmask(DefineBitmask::GROUND);
	bodyBullet->setTag(SKILL_TAG);
	this->setPhysicsBody(bodyBullet);
	return true;
}

bool Bullet::loadAnimations()
{
	Entity::loadAnimations();

	AnimationUtils::loadSpriteFrameCache("Skill/", "ball");
	AnimationUtils::createAnimation("ball", 1.0f);

	return true;
}