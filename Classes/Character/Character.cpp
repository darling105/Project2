﻿#include "Character.h"
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

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-jump");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-jump (1)");
	_model->runAction(animate);
	this->addChild(_model, 2);
	Size size = _model->getContentSize();
	Size newSize(_model->getContentSize().width / 1.6, _model->getContentSize().height / 1.1);
	physicBodyCharacter = PhysicsBody::createBox(newSize, PhysicsMaterial(1, 0, 0));
	physicBodyCharacter->setMass(0.3f);
	physicBodyCharacter->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBodyCharacter->setCollisionBitmask(DefineBitmask::GROUND);
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND /*| DefineBitmask::STAIR*/);
	physicBodyCharacter->setRotationEnable(false);
	physicBodyCharacter->setGravityEnable(true);
	physicBodyCharacter->setDynamic(true);
	physicBodyCharacter->setTag(CHARACTER_TAG);
	this->setPhysicsBody(physicBodyCharacter);


	//Vec2 position = _model->getPosition(); // Get the current position of the sprite
	//Vec2 topLeftCharacterPosition = Vec2((position.x - size.width * _model->getAnchorPoint().x) + 3.0f,
	//	position.y + size.height * (1 - _model->getAnchorPoint().y));

	//auto topleftCharacterPoint = Node::create();
	//auto physicsBodyTopLeftCharacter = PhysicsBody::createCircle(0.5, PhysicsMaterial(1, 1, 0));
	//physicsBodyTopLeftCharacter->setDynamic(false);
	//physicsBodyTopLeftCharacter->setRotationEnable(false);
	//topleftCharacterPoint->setPhysicsBody(physicsBodyTopLeftCharacter);
	//topleftCharacterPoint->setPosition(topLeftCharacterPosition);
	//this->addChild(topleftCharacterPoint);

	//Vec2 topRightCharacterPosition = Vec2((position.x + size.width * (1 - _model->getAnchorPoint().x)) - 3.0f,
	//	position.y + size.height * (1 - _model->getAnchorPoint().y));

	//auto topRightCharacterPoint = Node::create();
	//auto physicsBodyTopRightCharacter = PhysicsBody::createCircle(0.5, PhysicsMaterial(1, 1, 0));
	//physicsBodyTopRightCharacter->setDynamic(false);
	//physicsBodyTopRightCharacter->setRotationEnable(false);
	//topRightCharacterPoint->setPhysicsBody(physicsBodyTopRightCharacter);
	//topRightCharacterPoint->setPosition(topRightCharacterPosition);
	//this->addChild(topRightCharacterPoint);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Character::callbackOnContactBegin, this);
	//listener->onContactSeparate = CC_CALLBACK_1(Character::callbackOnContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new CharacterIdleState());
	_stateMachine->addState("run", new CharacterRunState());
	_stateMachine->addState("jump", new CharacterRunState());
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
	//AudioManager::getInstance()->playSFX("jump.mp3");
	_isOnGround = false;
	if (!_isJumping) {
	this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 60);
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

int Character::getNumberOfCharacters() {
	return _characters.size();
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
			physicBodyCharacter->setVelocity(Vec2::ZERO);
		}
	}
	return true;
}


void Character::callbackOnContactSeparate(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return;
	auto target = (nodeA == this) ? nodeB : nodeA;
	if (target->getTag() == PhysicGround::TAG_GROUND && target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		log("OnAir");
		_isOnGround = false;
	}
}

void Character::update(float dt) {
	if (_isOnGround || _isJumping) {
		_physicsBody->setVelocity(Vec2(0, _physicsBody->getVelocity().y));

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
}
