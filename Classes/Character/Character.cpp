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
#include "Score/Score.h"
#include "Objects/Platform/Platform.h"



std::vector<Character*> Character::_characters;
Character* Character::_instance;

std::vector<int> checkpointContacted;


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


void Character::getMap(std::string mapLevel)
{
	this->mapLevel = mapLevel;
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
	Size newSize(_model->getContentSize().width / 1.8, _model->getContentSize().height / 1.15);
	physicBodyCharacter = PhysicsBody::createBox(newSize, PhysicsMaterial(1, 0, 0));
	physicBodyCharacter->setMass(0.3f);
	physicBodyCharacter->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBodyCharacter->setCollisionBitmask(DefineBitmask::GROUND | DefineBitmask::PLATFORM);
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR | DefineBitmask::FINISH |
		DefineBitmask::SPIKE | DefineBitmask::COIN | DefineBitmask::ENEMY | DefineBitmask::BULLET | DefineBitmask::CHECKPOINT | DefineBitmask::PLATFORM);
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
	_stateMachine->addState("hurt", new CharacterHurtState());
	_stateMachine->setCurrentState("idle");
	this->addChild(_stateMachine);

	checkpointContacted.resize(10, false);

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
	aniNames.push_back(_info->_entityName + "-hurt");

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
			this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 28);
			_isJumping = true;
			_jumpCooldown = 0.62f;
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
	_baseSpeed = 12;
	this->scheduleUpdate();
	_stateMachine->scheduleUpdate();
}

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
			_isOnGround = true;
			_isJumping = false; 
		}
		else {
			_physicsBody->setVelocity(Vec2::ZERO);
		}
	}
	if (
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::PLATFORM) {
		if (target->getPositionY() < this->getPositionY())
		{
			_isOnPlatform = true;
			_isJumping = false;
		}
		else {
			_physicsBody->setVelocity(Vec2::ZERO);
		}
	}
	 if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) 
	{
		_isOnStair = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::FINISH)
	{
		_isOnFinish = true;
	}
	/*else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::ENEMY)
	 {
		 _isContactedEnemy = true;
	 }*/
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::SPIKE)
	{
		_isOnSpike = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::COIN)
	{
		_isPickedCoin = true;
	}
	else if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHECKPOINT) {
		 int tag = target->getTag();
		 if (tag >= 1 && tag <= 10) {
			 int checkpointIndex = tag - 1; // Chuyển đổi từ tag thành chỉ số mảng
			 if (!checkpointContacted[checkpointIndex]) {
				 _isContactedCheckPoint = true;
				 indexCheckPoint++;
				 checkpointContacted[checkpointIndex] = true; // Cập nhật trạng thái của checkpoint
				 check = target->getPosition();
			 }
		 }
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
	if (
		target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::PLATFORM) {
		 
			_isOnPlatform = false;
			_isJumping = true;
		
	}
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR) 
	{
		_isOnStair = false;
	}
	 /*if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::ENEMY)
	{
		_isContactedEnemy = false;
	}*/
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
	if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::BULLET) {
		_isContactedSkills = false;
	}
	return true;
}

void Character::update(float dt) {
	_jumpCooldown -= dt;
	if (_isOnGround || _isJumping) {
		log("onGround");
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
	if (_isOnStair) 
	{
		physicBodyCharacter->setGravityEnable(false);
		physicBodyCharacter->setVelocity(Vec2::ZERO);
		if (_isUpButtonDown) {
			physicBodyCharacter->applyImpulse(Vec2(0, 1) * 10);
		}
		if (_isDownButtonDown) {
			physicBodyCharacter->applyImpulse(Vec2(0, -1) * 10);
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
	if (_isOnFinish) 
	{
		_isMap1Completed = true;
		GameManager::getInstance()->endMap();
	}

	if (_isOnSpike || _isContactedSkills || _isContactedEnemy)
	{
		_retryCount--;
		if (_retryCount > 0) {
		if (indexCheckPoint >= 0) {
			this->setPosition(check);
		}
		}

	}
	if (_retryCount == 0)
	{
		auto _score = Score::getInstance();
		auto _highScore = _score->getScore();
		_score->saveToFile(mapLevel, _highScore);
		this->unscheduleUpdate();
		this->getPhysicsBody()->setVelocity(Vec2::ZERO);
		GameManager::getInstance()->gameOver();
		reset();
	}
	
	if (_isContactedCheckPoint)
	{
		log("check");
	}

	auto _healBar = HealthController::getInstance();
	_healBar->setCurrentHealth(_retryCount);
}
bool Character::_isMap1Completed = false;
void Character::reset()
{
	_retryCount = 3;
	Score::getInstance()->reset();
}

void Character::resetInstance() {
	// Đặt thể hiện của Character về nullptr
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}

	// Xóa tất cả các nhân vật từ vector _characters
	for (auto character : _characters) {
		delete character;
	}
	_characters.clear();
}
