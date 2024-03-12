#include "Void.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Character/Character.h"
#include "State/VoidIdleState.h"
#include "Skill/Bullet.h"

Void* Void::create(EntityInfo* info)
{
    auto newObject = new Void();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Void::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
    _model->setAnchorPoint(Vec2(0.7, 0.5));
    _model->setScale(0.75f);
    this->addChild(_model);

    Size size(_model->getContentSize().width / 1.5, _model->getContentSize().height / 1.5);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    this->setPhysicsBody(enemyPhysicBody);


    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("idle", new VoidIdleState());
    _enemyStateMachine->setCurrentState("idle");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Void::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-idle");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Void/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

void Void::update(float dt)
{

    EntityInfo info("character");
    Vec2 characterPosition = Character::getInstance(&info)->getCharacter(0)->getPosition();
    float creepPositionX = this->getPositionX();
    float creepPositionY = this->getPositionY();
    float creepHeight = 600.0f;

    if (characterPosition.x > creepPositionX + 20 && characterPosition.x < creepPositionX + 20 + 950
        && characterPosition.y < creepPositionY + (creepHeight / 4) && characterPosition.y > creepPositionY - creepHeight ) {
        shoot(dt);
    }
    else if (characterPosition.x < creepPositionX - 20 && characterPosition.x > creepPositionX - 20 - 950
        && characterPosition.y < creepPositionY + (creepHeight / 4) && characterPosition.y  > creepPositionY - creepHeight ) {
        shoot(dt);
    }
}

void Void::shoot(float dt)
{
    _countTime += dt;
    if (_countTime >= _timeShoot) {
        auto bullet = Bullet::create(new EntityInfo("ball"));
        bullet->setPosition(this->getPosition());
        bullet->setOwner(this);
        this->getParent()->addChild(bullet, 4);
        auto bulletBody = bullet->getPhysicsBody();
        if (_skillDirection == Vec2(0,-1)) {
            bulletBody->setVelocity(Vec2(0, -60));
        }
        else if (_skillDirection == Vec2(0, 1)) {
            bulletBody->setVelocity(Vec2(0, 60));
        }
        else if (_skillDirection == Vec2(-1, 0)) {
            bulletBody->setVelocity(Vec2(-60, 0));
        }
        else if (_skillDirection == Vec2(1, 0)) {
            bulletBody->setVelocity(Vec2(60, 0));
        }
        bulletBody->setGravityEnable(false);
        _countTime = 0.0f;
    }
    this->setRotation(_rotation);
}


void Void::setupVoid(float rotation, float timeShoot ,Vec2 skillDirection)
{
    _rotation = rotation;
    _timeShoot = timeShoot;
    _skillDirection = skillDirection;
}


