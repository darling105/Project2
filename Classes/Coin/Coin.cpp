#include "Coin.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "Character/Character.h"
#include "DefineBitmask.h"
#include "Score/Score.h"
#include "AudioManager/AudioManager.h"
#include "AudioEngine.h"

Coin* Coin::create(EntityInfo* info)
{
	auto newObject = new Coin();
	if (newObject != nullptr && newObject->init(info))
	{
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
	_info = info;
	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
	_model->runAction(animate);
	this->addChild(_model);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Coin::callbackOnContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	float halfCicle = _model->getContentSize().width / 3;
	auto coinPhysicBody = PhysicsBody::createCircle(halfCicle, PhysicsMaterial(1, 0, 0));
	coinPhysicBody->setCategoryBitmask(DefineBitmask::COIN);
	coinPhysicBody->setCollisionBitmask(DefineBitmask::NON);
	coinPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
	coinPhysicBody->setRotationEnable(false);
	coinPhysicBody->setGravityEnable(false);
	this->setPhysicsBody(coinPhysicBody);

	return true;
}

bool Coin::loadAnimations()
{
	Entity::loadAnimations();

	AnimationUtils::loadSpriteFrameCache("Coin/", "coin-idle");
	AnimationUtils::createAnimation("coin-idle", 1.0f);

	return true;
}

bool Coin::callbackOnContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;
	auto target = (nodeA == this) ? nodeA : nodeB;
	if (target) {
		_isPicked = true;
	}

	Score::getInstance()->update(10);

	AnimationUtils::loadSpriteFrameCache("Coin/", "coin-picked");
	AnimationUtils::createAnimation("coin-picked", 0.1f);

	auto explosion = Sprite::createWithSpriteFrameName("./coin-picked (1)");

	explosion->setPosition(this->getPosition());

	this->getParent()->addChild(explosion, this->getLocalZOrder());

	auto animation = AnimationCache::getInstance()->getAnimation("coin-picked");
	auto animate = Animate::create(animation);
	auto removeExplosion = CallFunc::create([explosion]() {
		explosion->removeFromParentAndCleanup(true);
		});

	auto sequence = Sequence::create(animate, removeExplosion, nullptr);
	explosion->runAction(sequence);
	return false;

}

void Coin::update(float dt)
{
	if (_isPicked) {
		AudioManager::getInstance()->playSFX("coin.mp3");
		this->removeFromParentAndCleanup(true);
	}
}