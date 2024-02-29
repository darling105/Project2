#include "Skill.h"
#include "DefineBitmask.h"
#include "AnimationUtilities/AnimationUtils.h"

//#include "IDamageable.h"

Skill* Skill::create(EntityInfo* info)
{
	auto newObject = new Skill();
	if (newObject != nullptr && newObject->init(info)) {
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Skill::init(EntityInfo* info)
{
	if (!Entity::init(info)) {
		return false;
	}

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName);
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + " (1)");
	_model->runAction(animate);
	this->addChild(_model, 2);

	// Tạo physics body cho đạn
	auto bodyBullet = PhysicsBody::createCircle(_model->getContentSize().height / 4, PhysicsMaterial(1, 0, 1));
	bodyBullet->setContactTestBitmask(DefineBitmask::BULLET);
	bodyBullet->setCollisionBitmask(DefineBitmask::GROUND);
	bodyBullet->setTag(SKILL_TAG);
	this->setPhysicsBody(bodyBullet);

	// Thêm listener cho sự kiện va chạm
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Skill::callbackOnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Skill::loadAnimations()
{
	Entity::loadAnimations();

	AnimationUtils::loadSpriteFrameCache("Skill/", "fireskill");
	AnimationUtils::createAnimation("fireskill", 1.0f);

	return true;
}


bool Skill::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	/*log("a: %d | b: %d", nodeA->getPhysicsBody()->getCategoryBitmask()
		, nodeB->getPhysicsBody()->getCategoryBitmask());
	log("a & b: %d", (nodeA->getPhysicsBody()->getCategoryBitmask() | nodeB->getPhysicsBody()->getCategoryBitmask()));*/

	/*auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_owner);
	}*/

	//this->removeFromParentAndCleanup(true);

	return false;
}

