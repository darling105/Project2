#include "Bat.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/BatPatrolState.h"

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
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    _model->setAnchorPoint(Vec2(0.7, 0.5));
    this->addChild(_model);

    /*auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Bat::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Bat::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);*/

    Size size(_model->getContentSize().width, _model->getContentSize().height);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    this->setPhysicsBody(enemyPhysicBody);
    enemyPhysicBody->setTag(ENEMY_TAG);

    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("patrol", new BatPatrolState());
    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Bat::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Bat/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

//bool Bat::callbackOnContactBegin(PhysicsContact& contact)
//{
//    nodeA = contact.getShapeA()->getBody()->getNode();
//    nodeB = contact.getShapeB()->getBody()->getNode();
//    if (nodeA != this && nodeB != this) return false;
//    if (nodeA->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER ||
//        nodeB->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER)
//    {
//        _isContactCharacter = true;
//    }
//    AnimationUtils::loadSpriteFrameCache("Enemy/Bat/", "creep-death");
//    AnimationUtils::createAnimation("creep-death", 1.25f);
//
//    auto explosion = Sprite::createWithSpriteFrameName("./creep-death (1)");
//
//    explosion->setPosition(this->getPosition());
//
//    this->getParent()->addChild(explosion, this->getLocalZOrder());
//
//    auto animation = AnimationCache::getInstance()->getAnimation("creep-death");
//    auto animate = Animate::create(animation);
//    auto removeExplosion = CallFunc::create([explosion]() {
//        explosion->removeFromParentAndCleanup(true);
//        });
//
//    auto sequence = Sequence::create(animate, removeExplosion, nullptr);
//    explosion->runAction(sequence);
//    return false;
//}
//
//bool Bat::callbackOnContactSeparate(PhysicsContact& contact)
//{
//    nodeA = contact.getShapeA()->getBody()->getNode();
//    nodeB = contact.getShapeB()->getBody()->getNode();
//    if (nodeA != this && nodeB != this) return false;
//    if (nodeA->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER ||
//        nodeB->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER)
//    {
//        _isContactCharacter = false;
//    }
//    return true;
//}

void Bat::onEnter()
{
    Entity::onEnter();
    this->scheduleUpdate();
}

void Bat::setupBat(float patrolSpeed, Vec2 initialMoveDirection)
{
    _patrolSpeed = patrolSpeed;
    _initialMoveDirection = initialMoveDirection;
}
