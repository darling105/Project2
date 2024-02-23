#include "Character.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
#include "PhysicRender/Stair.h"
#include "AudioManager/AudioManager.h"
#include "audio/include/AudioEngine.h"


std::vector<Character*> Character::_characters;
Character* Character::_instance;

Character* Character::getInstance(EntityInfo* info)
{
	if (_instance == nullptr)
	{
		_instance = new Character();
		_instance->init(info);
		_instance->retain();
	}
	return _instance;
}


bool Character::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Character failed!");
		return false;
	}

	AudioManager* audioManager = AudioManager::getInstance();

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
	_model->runAction(animate);
	this->addChild(_model, 2);
	Size size = _model->getContentSize();
	Size newSize(_model->getContentSize().width / 1.6, _model->getContentSize().height / 1.1);
	physicBodyCharacter = PhysicsBody::createBox(newSize, PhysicsMaterial(1, 0, 0));
	physicBodyCharacter->setMass(0.3f);
	physicBodyCharacter->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBodyCharacter->setCollisionBitmask(DefineBitmask::GROUND);
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR);
	physicBodyCharacter->setRotationEnable(false);
	physicBodyCharacter->setTag(CHARACTER_TAG);
	this->setPhysicsBody(physicBodyCharacter);


	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Character::callbackOnContactBegin, this);
	listener->onContactSeparate = CC_CALLBACK_1(Character::callbackOnContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new CharacterIdleState());
	_stateMachine->addState("run", new CharacterRunState());
	_stateMachine->addState("jump", new CharacterJumpState());
	_stateMachine->setCurrentState("idle");
	this->addChild(_stateMachine);
	return true;
}

bool Character::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "-idle");
	aniNames.push_back(_info->_entityName + "-run");
	aniNames.push_back(_info->_entityName + "-jump");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Character/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}


void Character::addCharacter(EntityInfo* info) {
	Character* _newCharacter = new Character();
	if (_newCharacter->init(info)) {
		_characters.push_back(_newCharacter);
	}
	else {
		delete _newCharacter;
	}
}

Character* Character::getCharacter(int index) {
	if (index >= 0 && index < _characters.size()) {
		return _characters[index];
	}
	return nullptr;
}



void Character::jump()
{
	_isOnGround = false;
	if (!_isJumping) {
	this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 80);
	_isJumping = true;
	}
}

void Character::moveLeft()
{
	this->getPhysicsBody()->applyImpulse(Vec2(-1, 0) * 40);
}

void Character::moveRight()
{
	this->getPhysicsBody()->applyImpulse(Vec2(1, 0) * 40);
}

void Character::setLeftButtonDown(bool isPressed)
{
	_isLeftButtonDown = isPressed;
}

void Character::setUpButtonDown(bool isPressed)
{

	_isUpButtonDown = isPressed;
}

void Character::setRightButtonDown(bool isPressed)
{
	_isRightButtonDown = isPressed;
}

void Character::setDownButtonDown(bool isPressed)
{
	_isDownButtonDown = isPressed;
}

int Character::getNumberOfCharacters() {
	return _characters.size();
}

void Character::onEnter()
{
	Entity::onEnter();
	this->scheduleUpdate();
}

bool Character::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? nodeB : nodeA;

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		if (target->getPosition().y < this->getPosition().y)
		{
			log("onGround");
			_isOnGround = true;
			_isJumping = false; 
		}
		else {
			_physicsBody->setVelocity(Vec2::ZERO);
		}
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) {
		_isOnStair = true;
	}
	return true;
}


bool Character::callbackOnContactSeparate(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? nodeB : nodeA;

	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) {
		_isOnStair = false;
	}
	return true;
}

void Character::update(float dt) {
	if (_isOnGround || _isJumping) {
		physicBodyCharacter->setVelocity(Vec2(0, physicBodyCharacter->getVelocity().y));

		if (_isLeftButtonDown) {
			moveLeft();
		}
		if (_isRightButtonDown) {
			moveRight();
		}
		if (_isUpButtonDown && _isOnGround) { // Chỉ cho nhảy khi đang ở trên mặt đất
			jump();
		}
	}
	if (_isOnStair) {
		physicBodyCharacter->setGravityEnable(false);
		physicBodyCharacter->setVelocity(Vec2::ZERO);
		if (_isUpButtonDown) {
			physicBodyCharacter->applyImpulse(Vec2(0, 1) * 40);
		}
		if (_isDownButtonDown) {
			physicBodyCharacter->applyImpulse(Vec2(0, -1) * 40);
		}
		if (_isLeftButtonDown) {
			moveLeft();
		}
		if (_isRightButtonDown) {
			moveRight();
		}
	}
	else {
		physicBodyCharacter->setGravityEnable(true);
	}

}
