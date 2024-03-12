#include "Ghost.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/GhostPatrolState.h"
#include "State/GhostAppearState.h"
#include "State/GhostDesappearState.h"
#include "State/GhostDeathState.h"
#include "State/GhostFootstepState.h"

Ghost* Ghost::create(EntityInfo* info)
{
    auto newObject = new Ghost();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Ghost::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Ghost::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Ghost::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width / 1.3, _model->getContentSize().height);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    this->setPhysicsBody(enemyPhysicBody);


    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("patrol", new GhostPatrolState());
    _enemyStateMachine->addState("appear", new GhostAppearState());
    _enemyStateMachine->addState("desappear", new GhostDesappearState());
    _enemyStateMachine->addState("death", new GhostDeathState());
    _enemyStateMachine->addState("footstep", new GhostFootstepState());
    _enemyStateMachine->setCurrentState("appear");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Ghost::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    aniNames.push_back(_info->_entityName + "-appear");
    aniNames.push_back(_info->_entityName + "-desappear");
    aniNames.push_back(_info->_entityName + "-death");
    aniNames.push_back(_info->_entityName + "-footstep");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Ghost/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

bool Ghost::callbackOnContactBegin(PhysicsContact& contact)
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
        if (_character->getPosition().y >= this->getPosition().y + 26) {

            _isContactCharacter = true;

            AnimationUtils::loadSpriteFrameCache("Enemy/Ghost/", "pupple-death");
            AnimationUtils::createAnimation("pupple-death", 1.25f);
            auto explosion = Sprite::createWithSpriteFrameName("./pupple-death (1)");
            explosion->setPosition(this->getPosition());
            this->getParent()->addChild(explosion, this->getLocalZOrder());
            auto animation = AnimationCache::getInstance()->getAnimation("pupple-death");
            auto animate = Animate::create(animation);
            auto removeExplosion = CallFunc::create([explosion]() {
                explosion->removeFromParentAndCleanup(true);
                });
            auto sequence = Sequence::create(animate, removeExplosion, nullptr);
            explosion->runAction(sequence);

            _character->getPhysicsBody()->setVelocity(Vec2(0, 1) * 240);
        }
        else {
            _character->_isContactedEnemy = true;
        }
    }

    return false;
}

bool Ghost::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        if (_character->getPosition().y >= this->getPosition().y + 26) {
            _character->_isContactedEnemy = false;
        }
        else {
            _character->_isContactedEnemy = false;
        }
    }
    return false;
}

void Ghost::update(float dt)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    if (_isContactCharacter) {
        this->removeFromParentAndCleanup(true);
    }
    _countTime += dt;
    if (_countTime >= 1.0f) {
        _appear = true;
    }
    else {
        _appear = false;
    }
    if (_countTime >= 5.0f) {
        _patrol = true;
    }
    else {
        _patrol = false;
    }
    if (_countTime >= 6.0f) {
        _desappear = true;
    }
    else {
        _desappear = false;
    }
    if (_countTime >= 10.0f) {
        _footstep = true;
        _countTime = 0.0f;
    }
    else {
        _footstep = false;
    }

    _countSpeed += dt;
    if (movingLeft && _countSpeed >= 3.0f) {
        movingRightFirst();
        _countSpeed = 0.0f;
    }
    else if (movingRight && _countSpeed >= 3.0f) {
        movingLeftFirst();
        _countSpeed = 0.0f;
    }
}

void Ghost::movingLeftFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(-1, 0) * _patrolSpeed);
    _model->setFlippedX(false);
    movingLeft = true;
    movingRight = false;
}

void Ghost::movingRightFirst()
{
    this->getPhysicsBody()->setVelocity(Vec2(1, 0) * _patrolSpeed);
    _model->setFlippedX(true);
    movingRight = true;
    movingLeft = false;
}

void Ghost::setSpeed(float newVal)
{
    _patrolSpeed = newVal;
}

