#include "Character.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
//#include "Enemy/Enemy.h"
//#include "KeyBoardInput.h"

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
	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
	_model->setScale(1.5);
	_model->runAction(animate);
	this->addChild(_model);

	Size newSize(_model->getContentSize().width / 1.15, _model->getContentSize().height * 1.4);
	physicBodyCharacter = PhysicsBody::createBox(newSize, PhysicsMaterial(1, 0, 1));
	physicBodyCharacter->setMass(0.3f);
	physicBodyCharacter->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBodyCharacter->setCollisionBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR);
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR);
	physicBodyCharacter->setRotationEnable(false);
	//physicBodyCharacter->setGravityEnable(true);
	//physicBodyCharacter->setDynamic(true);
	physicBodyCharacter->setTag(CHARACTER_TAG);
	this->setPhysicsBody(physicBodyCharacter);


	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Character::callbackOnContactBegin, this);
	listener->onContactSeparate = CC_CALLBACK_1(Character::callbackOnContactSeparate, this);
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
	this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 60);
}

void Character::moveLeft()
{
	this->getPhysicsBody()->applyImpulse(Vec2(-1, 0) * 25);
}

void Character::moveRight()
{
	this->getPhysicsBody()->applyImpulse(Vec2(1, 0) * 25);
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


bool Character::callbackOnContactBegin(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? nodeB : nodeA;

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		if (target->getPosition().y < this->getPosition().y)
		{
			log("onGround");
			physicBodyCharacter->setVelocity(Vec2::ZERO);
			_isOnGround = true;
		}
		else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) {
			_isOnStair = true;
			physicBodyCharacter->setVelocity(Vec2::ZERO);
			log("onStair");

		}
		else {
			physicBodyCharacter->setVelocity(Vec2::ZERO);
		}
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) {
		_isOnStair = true;
		physicBodyCharacter->setVelocity(Vec2::ZERO);
		log("onStair");
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
	else {
		_isOnStair = false;
	}
}





void Character::update(float dt) {
	if (_isOnGround) {

	if (_isUpButtonDown) {
		//log("Character is on the ground");
		jump();
		//log("toc do:%f", physicBodyCharacter->getVelocity().length());
	}
	if (_isLeftButtonDown) {
		_physicsBody->setVelocity(Vec2::ZERO);
		moveLeft();
	}
	if (_isRightButtonDown)
	{
		_physicsBody->setVelocity(Vec2::ZERO);
		moveRight();
	}
	}
	else {

		if (_isLeftButtonDown) {
			_physicsBody->setVelocity(Vec2(0, _physicsBody->getVelocity().y));
			moveLeft();
		}
		if (_isRightButtonDown)
		{
			_physicsBody->setVelocity(Vec2(0, _physicsBody->getVelocity().y));
			moveRight();
		}
	}

}















