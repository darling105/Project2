#include "Trampoline.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "Character/Character.h"
#include "DefineBitmask.h"
#include "AudioManager/AudioManager.h"
#include "AudioEngine.h"

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
	_model->setScale(1.5);
	_model->setAnchorPoint(Vec2(0.5, 0.2));
	this->addChild(_model);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Trampoline::callbackOnContactBegin, this);
	listener->onContactSeparate = CC_CALLBACK_1(Trampoline::callbackOnContaceSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size size(_model->getContentSize().width, _model->getContentSize().height / 1.7);
	auto trampolinePhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1, 0, 0));
	trampolinePhysicBody->setCategoryBitmask(DefineBitmask::TRAMPOLINE);
	trampolinePhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
	trampolinePhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
	trampolinePhysicBody->setRotationEnable(false);
	this->setPhysicsBody(trampolinePhysicBody);

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
	AnimationUtils::createAnimation("trampoline-active", 0.2f);

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

bool Trampoline::callbackOnContaceSeparate(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;
	auto target = (nodeA == this) ? nodeA : nodeB;
	if (target) {
		_isPicked = false;
	}
	return false;
}

void Trampoline::update(float dt)
{
	EntityInfo info("character");
	auto _charInstance = Character::getInstance(&info);
	auto _char = _charInstance->getCharacter(0);
	if (_isPicked) {
		AudioManager::getInstance()->playSFX("trampoline.mp3");
		log("contact");
		_model->setVisible(false);
		_char->getPhysicsBody()->setVelocity(Vec2::ZERO);
		_char->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 35);
	}
	else {
		_model->setVisible(true);
	}
}