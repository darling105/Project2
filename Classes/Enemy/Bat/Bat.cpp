#include "Bat.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/BatPatrolState.h"
#include "State/BatDeathState.h"
#include "PhysicRender/PhysicGround.h"
#include "AudioManager/AudioManager.h"
#include "AudioEngine.h"
#include <algorithm>;

Bat* Bat::create(EntityInfo* info)
{
    auto newObject = new Bat();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Bat::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    timeDeath = 0.0f;
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    _model->setAnchorPoint(Vec2(0.7, 0.5));
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Bat::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Bat::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width, _model->getContentSize().height - 10);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    this->setPhysicsBody(enemyPhysicBody);

    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("patrol", new BatPatrolState());
    _enemyStateMachine->addState("death", new BatDeathState());
    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Bat::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    aniNames.push_back(_info->_entityName + "-death");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Bat/", name);
        AnimationUtils::createAnimation(name, 0.85f);
    }
    return true;
}

bool Bat::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if(target) {
        if (_character->getPosition().y >= this->getPosition().y + 18) {
            _isContactCharacter = true;
            _character->_isContactedEnemy = false;
            _character->getPhysicsBody()->setVelocity(Vec2(0, 1) * 40);
        }
        else {
            _character->_isContactedEnemy = true;
        }
    }
    return false;
}

bool Bat::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        if (_character->getPosition().y >= this->getPosition().y + 18) {
            _character->_isContactedEnemy = false;
        }
        else {
            _character->_isContactedEnemy = false;
        }
    }
    return false;
}


void Bat::update(float dt)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    if (_isContactCharacter) {
        AudioManager::getInstance()->playSFX("touch_enemy.mp3");
        this->getPhysicsBody()->setGravityEnable(true);
            timeDeath += dt;  
    }
    if (timeDeath >= 0.8f) {
        this->removeFromParentAndCleanup(true);
        timeDeath = 0.0f;
        _isContactCharacter = false;

    }
}




void Bat::onEnter()
{
    Entity::onEnter();
}





void Bat::setupBat(float patrolSpeed, Vec2 initialMoveDirection)
{
    _patrolSpeed = patrolSpeed;
    _initialMoveDirection = initialMoveDirection;
}
