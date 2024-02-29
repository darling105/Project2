#include "Trampoline.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

Trampoline* Trampoline::create(EntityInfo* info)
{
	auto newObject = new Trampoline();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Trampoline::init(EntityInfo* info)
{
	if (!Entity::init(info)) {
		return false;
	}
	_info = info;
	/*auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(aniIdle));*/
	_model = Sprite::create("Objects/Trampoline/" + _info->_entityName + ".png");
	//_model->runAction(animate);
	this->addChild(_model);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Trampoline::callbackOnContactBegin, this);
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

bool Trampoline::loadAnimations()
{
	Entity::loadAnimations();
	return true;
}

bool Trampoline::callbackOnContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;
	auto target = (nodeA == this) ? nodeA : nodeB;
	if (target) {
		_isPicked = true;
	}

	AnimationUtils::loadSpriteFrameCache("Objects/Trampoline/", "trampoline-active");
	AnimationUtils::createAnimation("trampoline-active", 0.5f);

	auto explosion = Sprite::createWithSpriteFrameName("./trampoline-active (1)");

	explosion->setPosition(this->getPosition());

	this->getParent()->addChild(explosion, this->getLocalZOrder());

	auto animation = AnimationCache::getInstance()->getAnimation("trampoline-active");
	auto animate = Animate::create(animation);
	auto removeExplosion = CallFunc::create([explosion]() {
		explosion->removeFromParentAndCleanup(true);
		});

	auto sequence = Sequence::create(animate, removeExplosion, nullptr);
	explosion->runAction(sequence);
	return false;

}


void Trampoline::onEnter()
{
	Entity::onEnter();
	this->scheduleUpdate();
}

void Trampoline::update(float dt)
{
	if (_isPicked) {
		log("contact");
		//this->removeFromParentAndCleanup(false);
	}
}