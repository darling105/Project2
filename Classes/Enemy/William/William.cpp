#include "William.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Skill/Bullet.h"
#include "Character/Character.h"
#include "State/WilliamIdleState.h"

William* William::create(EntityInfo* info)
{
    auto newObject = new William();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool William::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _isAttack = false;
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
    _model->setAnchorPoint(Vec2(0.58, 0.4));
    _model->setScale(2.0f);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(William::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(William::callbackOnContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    Size size(_model->getContentSize().width * 1.8, _model->getContentSize().height * 1.6);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(true);
    this->setPhysicsBody(enemyPhysicBody);

    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("idle", new WilliamIdleState());
    _enemyStateMachine->setCurrentState("idle");
    this->addChild(_enemyStateMachine);

    return true;
}


bool William::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-idle");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/William/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }
    return true;
}

bool William::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        if (_character->getPosition().y >= this->getPosition().y + 48) {
            _isContactCharacter = true;
            AnimationUtils::loadSpriteFrameCache("Enemy/William/", "william-death");
            AnimationUtils::createAnimation("william-death", 1.25f);

            auto explosion = Sprite::createWithSpriteFrameName("./william-death (1)");
            explosion->setScale(2.0f);
            explosion->setFlippedX(true);
            explosion->setPosition(this->getPosition());

            this->getParent()->addChild(explosion, this->getLocalZOrder());

            auto animation = AnimationCache::getInstance()->getAnimation("william-death");
            auto animate = Animate::create(animation);
            auto removeExplosion = CallFunc::create([explosion]() {
                explosion->removeFromParentAndCleanup(true);
                });

            auto sequence = Sequence::create(animate, removeExplosion, nullptr);
            explosion->runAction(sequence);
            _character->getPhysicsBody()->setVelocity(Vec2(0, 1) * 40);
            _character->_isContactedEnemy = false;
        }
        else {
            _character->_isContactedEnemy = true;
        }
    }

    return false;
}

bool William::callbackOnContactSeparate(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    auto target = (nodeA == this) ? nodeA : nodeB;
    if (target) {
        if (_character->getPosition().y >= this->getPosition().y + 48) {
            _character->_isContactedEnemy = false;
        }
        else {
            _character->_isContactedEnemy = false;
        }
    }
    return false;
}


void William::update(float dt) {
    EntityInfo info("character");
    Vec2 characterPosition = Character::getInstance(&info)->getCharacter(0)->getPosition();
    float creepPositionX = this->getPositionX();
    float creepPositionY = this->getPositionY();
    float creepHeight = 64.0f;


    if (characterPosition.x > creepPositionX + 20 && characterPosition.x < creepPositionX + 20 + 125
        && characterPosition.y < creepPositionY - 20 + creepHeight && characterPosition.y  > creepPositionY - 20) {
        _rightRange = true;
        _leftRange = false;
    }
    else if (characterPosition.x < creepPositionX - 20 && characterPosition.x > creepPositionX - 20 - 125
        && characterPosition.y < creepPositionY - 20 + creepHeight && characterPosition.y  > creepPositionY - 20) {
        _rightRange = false;
        _leftRange = true;
    }
    else {
        _rightRange = false;
        _leftRange = false;

    }

    if (_isContactCharacter) {
        this->removeFromParentAndCleanup(true);
    }
}