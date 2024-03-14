#include "Saw.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"

Saw* Saw::create(EntityInfo* info)
{
    auto newObject = new Saw();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Saw::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    _model->runAction(animate);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Saw::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Saw::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto enemyPhysicBody = PhysicsBody::createCircle(_model->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setPositionOffset(Vec2(0, -_model->getContentSize().height * 0.4));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::NON);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    this->setPhysicsBody(enemyPhysicBody);

    this->setScale(0.8f);

    return true;
}

bool Saw::loadAnimations()
{
    Entity::loadAnimations();

    
        AnimationUtils::loadSpriteFrameCache("Objects/Saw/", "saw-patrol");
        AnimationUtils::createAnimation("saw-patrol", 1.0f);
    
    return true;
}

bool Saw::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    if (nodeA->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER ||
        nodeB->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER)
    {
       
            
        _character->_isContactedEnemy = true;

    }

    return false;
}

bool Saw::callbackOnContactSeparate(PhysicsContact& contact)
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

void Saw::update(float dt)
{
    _countSpeed += dt;
    if (movingLeft && _countSpeed >= 2.0f) {
        movingRightFirst();
        _countSpeed = 0.0f;
    }
    else if (movingRight && _countSpeed >= 2.0f) {
        movingLeftFirst();
        _countSpeed = 0.0f;
    }
}

void Saw::movingLeftFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(-1, 0) * _patrolSpeed);
    _model->setFlippedX(false);
    movingLeft = true;
    movingRight = false;
}

void Saw::movingRightFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(1, 0) * _patrolSpeed);
    _model->setFlippedX(true);
    movingRight = true;
    movingLeft = false;
}

void Saw::setSpeed(float newVal)
{
    _patrolSpeed = newVal;
}
