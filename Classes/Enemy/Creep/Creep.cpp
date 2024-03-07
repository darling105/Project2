#include "Creep.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Skill/Bullet.h"
#include "Character/Character.h"
#include "State/CreepAttackState.h"
#include "State/CreepPatrolState.h"

Creep* Creep::create(EntityInfo* info)
{
    auto newObject = new Creep();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Creep::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _isAttack = false;
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    _model->setAnchorPoint(Vec2(0.7, 0.5));
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Creep::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Creep::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width, _model->getContentSize().height);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(true);
    this->setPhysicsBody(enemyPhysicBody);
    enemyPhysicBody->setTag(ENEMY_TAG);

    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("patrol", new CreepPatrolState());
    _enemyStateMachine->addState("attack", new CreepAttackState());
    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Creep::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    aniNames.push_back(_info->_entityName + "-attack");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Creep/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

bool Creep::callbackOnContactBegin(PhysicsContact& contact)
{
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    if (nodeA->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER ||
        nodeB->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER)
    {
        _isContactCharacter = true;
    }
    AnimationUtils::loadSpriteFrameCache("Enemy/Creep/", "creep-death");
    AnimationUtils::createAnimation("creep-death", 1.25f);

    auto explosion = Sprite::createWithSpriteFrameName("./creep-death (1)");

    explosion->setPosition(this->getPosition());

    this->getParent()->addChild(explosion, this->getLocalZOrder());

    auto animation = AnimationCache::getInstance()->getAnimation("creep-death");
    auto animate = Animate::create(animation);
    auto removeExplosion = CallFunc::create([explosion]() {
        explosion->removeFromParentAndCleanup(true);
        });

    auto sequence = Sequence::create(animate, removeExplosion, nullptr);
    explosion->runAction(sequence);
    return false;
}

bool Creep::callbackOnContactSeparate(PhysicsContact& contact)
{
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    if (nodeA->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER ||
        nodeB->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::CHARACTER)
    {
        _isContactCharacter = false;
    }
    return true;
}


void Creep::update(float dt) {
    EntityInfo info("character");
    Vec2 characterPosition = Character::getInstance(&info)->getCharacter(0)->getPosition();
    float creepPositionX = this->getPositionX();
    float creepPositionY = this->getPositionY();
    float creepHeight = 32.0f;
    /*log("yPos Character: %f", characterPosition.y);
    log("yPos Enemy: %f", creepPositionY);*/
    if (characterPosition.x > creepPositionX + 20 && characterPosition.x < creepPositionX + 20 + 100
        && characterPosition.y < creepPositionY + creepHeight && characterPosition.y + 2 > creepPositionY ) {
        _rightRange = true;
        _leftRange = false;
        log("right");
        shoot(dt);
    }
    else if (characterPosition.x < creepPositionX - 20 && characterPosition.x > creepPositionX - 20 - 100
        && characterPosition.y < creepPositionY + creepHeight && characterPosition.y + 2 > creepPositionY) {
        _rightRange = false;
        _leftRange = true;
        log("left");
        shoot(dt);
    }
    else {
        _rightRange = false;
        _leftRange = false;

    }

    if (_isContactCharacter) {
        this->removeFromParentAndCleanup(true);
    }
}


void Creep::shoot(float dt)
{
    _isAttack = false;
    bulletTimer += dt;

    if (_isAttack) {
        if (bulletTimer >= bulletInterval) {
            bulletTimer = 0.0f;
        }
        else {
            return;
        }
    }

    if (bulletTimer >= bulletInterval) {
        for (int i = 0; i < 3; ++i) {
            auto bullet = Bullet::create(new EntityInfo("ball"));
            bullet->setPosition(this->getPosition());
            bullet->setOwner(this);
            this->getParent()->addChild(bullet, 4);
            auto bulletBody = bullet->getPhysicsBody();
            if (_leftRange) {
                bulletBody->setVelocity(Vec2(-300, 0));
                bulletBody->setGravityEnable(false);
                _isAttack = true;
            }
            if (_rightRange) {
                bulletBody->setVelocity(Vec2(300, 0));
                bulletBody->setGravityEnable(false);
                _isAttack = true;
            }
        }
        bulletTimer = 0.0f;
    }
}




void Creep::onEnter()
{
    Entity::onEnter();
    this->scheduleUpdate();
    bulletInterval = 0.5f;
}