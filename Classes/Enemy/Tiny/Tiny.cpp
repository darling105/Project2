#include "Tiny.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/TinyIdleState.h"
#include "State/TinyRunState.h"
#include "State/TinyJumpState.h"
#include "State/TinyExplodeState.h"
#include "State/TinyDeathState.h"

Tiny* Tiny::create(EntityInfo* info)
{
    auto newObject = new Tiny();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Tiny::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Tiny::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Tiny::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width / 1.3, _model->getContentSize().height);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    this->setPhysicsBody(enemyPhysicBody);


    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("idle", new TinyIdleState());
    _enemyStateMachine->addState("run", new TinyRunState());
    _enemyStateMachine->addState("jump", new TinyJumpState());
    _enemyStateMachine->addState("explode", new TinyExplodeState());
    _enemyStateMachine->addState("death", new TinyDeathState());
    _enemyStateMachine->setCurrentState("idle");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Tiny::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-idle");
    aniNames.push_back(_info->_entityName + "-run");
    aniNames.push_back(_info->_entityName + "-jump");
    aniNames.push_back(_info->_entityName + "-death");
    aniNames.push_back(_info->_entityName + "-explode");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Tiny/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

bool Tiny::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        _character->_isContactedEnemy = true;
    }
    return true;
}

bool Tiny::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
            _character->_isContactedEnemy = false;
    }
    return false;
}

void Tiny::update(float dt)
{
    EntityInfo info("character");
    Vec2 characterPosition = Character::getInstance(&info)->getCharacter(0)->getPosition();
    float creepPositionX = this->getPositionX();
    float creepPositionY = this->getPositionY();
    float creepHeight = 600.0f;

    if (characterPosition.x > creepPositionX + 20 && characterPosition.x < creepPositionX + 20 + 200
        && characterPosition.y < creepPositionY + (creepHeight / 4) && characterPosition.y > creepPositionY - creepHeight) {
        movingRightFirst();
        _isMoving = true;
    }
    else if (characterPosition.x < creepPositionX - 20 && characterPosition.x > creepPositionX - 20 - 200
        && characterPosition.y < creepPositionY + (creepHeight / 4) && characterPosition.y  > creepPositionY - creepHeight) {
        movingLeftFirst();
        _isMoving = true;
    }
    else {
        _isMoving = false;
    }

    if (_isMoving) {
        _countTime += dt;
        if (_countTime >= 1.0f) {
            _jump = true;
            this->getPhysicsBody()->setVelocity(Vec2(0, 1) * 40);
        }
    }

    if (_jump) {
        _countExplode += dt;
        if (_countExplode >= 0.2f) {
            _explode = true;
            auto body = this->getPhysicsBody();
            body->removeFromWorld();
            _model->setScale(1.5f);
            auto circleBody = PhysicsBody::createCircle(_model->getContentSize().width / 2);
            circleBody->setCategoryBitmask(DefineBitmask::ENEMY);
            circleBody->setCollisionBitmask(DefineBitmask::GROUND);
            circleBody->setContactTestBitmask(DefineBitmask::CHARACTER);
            this->setPhysicsBody(circleBody);
            this->getPhysicsBody()->setVelocity(Vec2(0, 1) * -60);
        }
    }
    if (_explode) {
        _countDeath += dt;
        if (_countDeath >= 0.8f) {
            auto body = this->getPhysicsBody();
            body->removeFromWorld();
            _model->setScale(1.0f);
            _dead = true;
        }
    }

    if (_dead) {
        _countRemove += dt;
        if (_countRemove >= 1.0f) {
            this->removeFromParentAndCleanup(true);
        }
    }
    
}

void Tiny::movingLeftFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(-1, 0) * _patrolSpeed);
    _model->setFlippedX(false);
    movingLeft = true;
    movingRight = false;
}

void Tiny::movingRightFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(1, 0) * _patrolSpeed);
    _model->setFlippedX(true);
    movingRight = true;
    movingLeft = false;
}

void Tiny::setSpeed(float newVal)
{
    _patrolSpeed = newVal;
}

