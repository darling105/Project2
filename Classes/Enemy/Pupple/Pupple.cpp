#include "Pupple.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/PupplePatrolState.h"

Pupple* Pupple::create(EntityInfo* info)
{
    auto newObject = new Pupple();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Pupple::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Pupple::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Pupple::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width / 1.2, _model->getContentSize().height / 1.5);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(true);
    this->setPhysicsBody(enemyPhysicBody);


    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("patrol", new PupplePatrolState());
    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);

    return true;
}

void Pupple::setupPupple(float patrolSpeed, Vec2 initialMoveDirection)
{
    _patrolSpeed = patrolSpeed;
    _initialMoveDirection = initialMoveDirection;
}

bool Pupple::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Pupple/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

bool Pupple::callbackOnContactBegin(PhysicsContact& contact)
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
        if (_character->getPosition().y >= this->getPosition().y + 20) {

        _isContactCharacter = true;

        AnimationUtils::loadSpriteFrameCache("Enemy/Pupple/", "pupple-death");
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

        _character->getPhysicsBody()->setVelocity(Vec2(0, 1) * 40);
        }
        else {
            _character->_isContactedEnemy = true;
        }
    }
    
    return false;
}

bool Pupple::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        if (_character->getPosition().y >= this->getPosition().y + 20) {
            _character->_isContactedEnemy = false;
        }
        else {
            _character->_isContactedEnemy = false;
        }
    }
    return false;
}

void Pupple::update(float dt)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    if (_isContactCharacter) {
        this->removeFromParentAndCleanup(true);
    }
}
