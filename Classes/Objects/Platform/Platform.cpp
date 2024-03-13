#include "Platform.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "PhysicRender/PhysicGround.h"

Platform* Platform::create(EntityInfo* info)
{
    auto newObject = new Platform();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Platform::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-run");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-run (1)");
    _model->runAction(animate);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Platform::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Platform::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width, _model->getContentSize().height);

    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::PLATFORM);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    enemyPhysicBody->setDynamic(false);
    this->setPhysicsBody(enemyPhysicBody);
    this->setScale(2.0f);
    return true;
}

bool Platform::loadAnimations()
{
    Entity::loadAnimations();


    AnimationUtils::loadSpriteFrameCache("Objects/Platform/", "platform-run");
    AnimationUtils::createAnimation("platform-run", 1.0f);

    return true;
}

bool Platform::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (this->getPositionY() < _character->getPositionY()) {

        _isContactCharacter = true;
    }
    else {
        _isContactCharacter = false;
    }
    return false;
}

bool Platform::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
        _isContactCharacter = false;
    return false;
}

void Platform::update(float dt)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    _countSpeed += dt;
    if (movingLeft && _countSpeed >= 4.5f) {
        movingRightFirst();
        _countSpeed = 0.0f;
    }
    else if (movingRight && _countSpeed >= 4.5f) {
        movingLeftFirst();
        _countSpeed = 0.0f;
    }
    if (_isContactCharacter && movingLeft) {
        _character->getPhysicsBody()->setVelocity(Vec2(-1, 0) * _patrolSpeed);

    }

    if (_isContactCharacter && movingRight) {
        _character->getPhysicsBody()->setVelocity(Vec2(1, 0) * _patrolSpeed);
    }

    if (_isContactCharacter) {
        _character->getPhysicsBody()->setVelocity(Vec2(_character->getPhysicsBody()->getVelocity().x, - 20));
        if (_character->_isLeftButtonDown) {
            _character->moveLeft();
        }
        if (_character->_isRightButtonDown) {
            _character->moveRight();
        }
    }
    
}

void Platform::movingLeftFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(-1, 0) * _patrolSpeed);
    movingLeft = true;
    movingRight = false;
}

void Platform::movingRightFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(1, 0) * _patrolSpeed);
    movingRight = true;
    movingLeft = false;
}

void Platform::setSpeed(float newVal)
{
    _patrolSpeed = newVal;
}
