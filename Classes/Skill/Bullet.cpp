#include "Bullet.h"
#include "DefineBitmask.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "PhysicRender/PhysicGround.h"

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
	bodyBullet->setCategoryBitmask(DefineBitmask::BULLET);
	bodyBullet->setCollisionBitmask(DefineBitmask::GROUND);
	bodyBullet->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::CHARACTER);
	bodyBullet->setTag(SKILL_TAG);
	this->setPhysicsBody(bodyBullet);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Bullet::callbackOnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Bullet::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		_isCollidedGround = true;
		this->removeFromParentAndCleanup(true);
	}
	else {
		_isCollidedCharacter = true;
	}

	return true;
}

bool Bullet::callbackOnContactSeparate(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		_isCollidedGround = false;
	}
	else {
		_isCollidedCharacter = false;
	}

	return true;
}

bool Bullet::loadAnimations()
{
	Entity::loadAnimations();

	AnimationUtils::loadSpriteFrameCache("Skill/", "ball");
	AnimationUtils::createAnimation("ball", 1.0f);

	return true;
}

//void Bullet::update(float dt)
//{
//	if (_isCollidedGround) {
//		this->removeFromParentAndCleanup(true);
//	}
//}

