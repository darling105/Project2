#include "Character.h"
#include "Utilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
#include "Enemy/Enemy.h"
#include "KeyBoardInput.h"

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
	_info = info;

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
	_model->runAction(animate);
	this->addChild(_model);

	physicBodyCharacter = PhysicsBody::createBox(_model->getContentSize() / 3, PhysicsMaterial(1, 0, 0));
	physicBodyCharacter->setMass(0.3f);
	physicBodyCharacter->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBodyCharacter->setCollisionBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR);
	physicBodyCharacter->setContactTestBitmask(DefineBitmask::GROUND | DefineBitmask::STAIR);
	physicBodyCharacter->setRotationEnable(false);
	physicBodyCharacter->setGravityEnable(true);
	physicBodyCharacter->setDynamic(true);
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
	aniNames.push_back(_info->_entityName + "_Idle_Down");
	aniNames.push_back(_info->_entityName + "_Idle_Right");
	aniNames.push_back(_info->_entityName + "_Jump_Down");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Hero/", name);
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
	 if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::STAIR){
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
		_isOnGround = false;
	}
	else{
		_isOnStair = false;
	}
}





void Character::update(float dt) {
	if (_isOnGround) {
		//log("Character is on the ground");
		physicBodyCharacter->setVelocity(Vec2::ZERO);
		 if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_SPACE)) {
			this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 80);
		}
		 if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_A)) {
			 this->getPhysicsBody()->applyImpulse(Vec2(-1, 0) * 40);
			
		 }
		 if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_D)) {
			 this->getPhysicsBody()->applyImpulse(Vec2(1, 0) * 40);
		 }
		 //log("toc do:%f", physicBodyCharacter->getVelocity().length());
	}
	else if (_isOnStair) {
		physicBodyCharacter->setVelocity(Vec2::ZERO);
		if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_W)) {
			this->getPhysicsBody()->applyImpulse(Vec2(0, 1) * 40);

		}
		if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_S)) {
			this->getPhysicsBody()->applyImpulse(Vec2(0, -1) * 40);
		}
	}
	else {
		this->getPhysicsBody()->setVelocity(Vec2(0, this->getPhysicsBody()->getVelocity().y));

		if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_A)) {
			this->getPhysicsBody()->applyImpulse(Vec2(-1, 0) * 40);
		}
		if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_D)) {
			this->getPhysicsBody()->applyImpulse(Vec2(1, 0) * 40);
		}
	}

	
}















