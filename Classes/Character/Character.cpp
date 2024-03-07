#include "Character.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
#include "PhysicRender/Stair.h"
#include "PhysicRender/Finish.h"
#include "Manager/GameManager.h"
#include "AudioManager/AudioManager.h"
#include "audio/include/AudioEngine.h"
#include "Manager/GameManager.h"
#include "Coin/Coin.h"
#include "Enemy/Creep/Creep.h"
#include "ButtonController/ButtonController.h"
#include "Maps/Map1.h"



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
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR | DefineBitmask::FINISH |
		DefineBitmask::SPIKE | DefineBitmask::COIN | DefineBitmask::ENEMY | DefineBitmask::BULLET);
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
	_stateMachine->addState("climb", new CharacterClimbState());
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
	aniNames.push_back(_info->_entityName + "-climb");

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
	if (_jumpCooldown <= 0.0f) {
		_isOnGround = false;
		if (!_isJumping) {
			this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 85);
			_isJumping = true;
			_jumpCooldown = 1.1f;
		}
	}
}


void Character::moveLeft()
{
	this->getPhysicsBody()->applyImpulse(Vec2(-1, 0) * _baseSpeed);
	if (!_isPickedCoin && !_isContactedEnemy)
	{
		AnimationUtils::loadSpriteFrameCache("Character/", "character-run-effect");
		AnimationUtils::createAnimation("character-run-effect", 0.025f);

		auto explosion = Sprite::createWithSpriteFrameName("./character-run-effect (1)");
		explosion->setScale(0.82f);
		explosion->setPosition(this->getPosition());

		this->getParent()->addChild(explosion, this->getLocalZOrder());

		auto animation = AnimationCache::getInstance()->getAnimation("character-run-effect");
		auto animate = Animate::create(animation);
		auto removeExplosion = CallFunc::create([explosion]() {
			explosion->removeFromParentAndCleanup(true);
			});

		auto sequence = Sequence::create(animate, removeExplosion, nullptr);
		explosion->runAction(sequence);
		explosion->setFlippedX(true);
	}
}

void Character::moveRight()
{
	this->getPhysicsBody()->applyImpulse(Vec2(1, 0) * _baseSpeed);
	if (!_isPickedCoin && !_isContactedEnemy) {
		AnimationUtils::loadSpriteFrameCache("Character/", "character-run-effect");
		AnimationUtils::createAnimation("character-run-effect", 0.025f);

		auto explosion = Sprite::createWithSpriteFrameName("./character-run-effect (1)");
		explosion->setScale(0.82f);
		explosion->setPosition(this->getPosition());

		this->getParent()->addChild(explosion, this->getLocalZOrder());

		auto animation = AnimationCache::getInstance()->getAnimation("character-run-effect");
		auto animate = Animate::create(animation);
		auto removeExplosion = CallFunc::create([explosion]() {
			explosion->removeFromParentAndCleanup(true);
			});

		auto sequence = Sequence::create(animate, removeExplosion, nullptr);
		explosion->runAction(sequence);
		explosion->setFlippedX(false);
	}
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

void Character::setPauseButtonDown(bool isPressed)
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
	_stateMachine->scheduleUpdate();
}

//void Character::onExit()
//{
//	Entity::onExit();
//	_stateMachine->retain();
//}

bool Character::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? nodeB : nodeA;

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		if (target->getPositionY() < this->getPositionY())
		{
			log("onGround");
			_isOnGround = true;
			_isJumping = false; 
		}
		else {
			_physicsBody->setVelocity(Vec2::ZERO);
		}
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) 
	{
		_isOnStair = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::FINISH)
	{
		_isOnFinish = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::SPIKE)
	{
		_isOnSpike = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::COIN)
	{
		_isPickedCoin = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::ENEMY) {
		_isContactedEnemy = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::BULLET) {
		_isContactedSkills = true;
	}
	return true;
}


bool Character::callbackOnContactSeparate(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? nodeB : nodeA;

	if (target->getTag() == PhysicGround::TAG_GROUND &&
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
		if (!_isOnGround) {
		_isOnGround = false;
		_isJumping = true;
		}
	}

	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) 
	{
		_isOnStair = false;
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::FINISH)
	{
		_isOnFinish = false;
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::SPIKE)
	{
		_isOnSpike = false;
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::COIN)
	{
		_isPickedCoin = false;
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::ENEMY)
	{
		_isContactedEnemy = false;
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::BULLET) {
		_isContactedSkills = false;
	}
	return true;
}

void Character::update(float dt) {
	_jumpCooldown -= dt;
	if (_isOnGround || _isJumping) {
		physicBodyCharacter->setVelocity(Vec2(0, physicBodyCharacter->getVelocity().y));

		if (_isLeftButtonDown ) {
			moveLeft();
		}
		if (_isRightButtonDown) {
			moveRight();
		}
		if (_isUpButtonDown && _isOnGround && _jumpCooldown <= 0.0f) { 
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
	if (_isOnFinish) {
		GameManager::getInstance()->endGame();
	}

	auto _healthController = HealthController::getInstance(3, "/Character/Health/Healthbar_full.png");

	if (_isOnSpike || _isContactedSkills)
	{
		log("%d", _retryCount);
		this->setPosition(Vec2(2500, 1200));
		log("GameOver");
		_retryCount--;
		

		float newHealth = _healthController->getCurrentHealth()  - 1;
		_healthController->setCurrentHealth(newHealth);

	}
	if (_retryCount == 0) {
		this->unscheduleUpdate();
		this->getPhysicsBody()->setVelocity(Vec2::ZERO);
		GameManager::getInstance()->gameOver();
		reset();
	}
}

void Character::reset()
{
	auto _healthController = HealthController::getInstance(3, "/Character/Health/Healthbar_full.png");
	_retryCount = 3;
	_healthController->setCurrentHealth(_retryCount);
	_baseSpeed = 60;
}
