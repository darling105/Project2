#include "Creep.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Skill/Skill.h"
#include "Character/Character.h"

Creep* Creep::_instance;
std::vector<Creep*> Creep::_enemies;


Creep* Creep::getInstance(EntityInfo* info) {
    if (_instance == nullptr) {
        _instance = new Creep();
        _instance->init(info);
        _instance->retain();
    }
    return _instance;
}

void Creep::addEnemy(EntityInfo* info)
{
    Creep* _newEnemy = new Creep();
    if (_newEnemy->init(info)) {
        _enemies.push_back(_newEnemy);
    }
    else {
        delete _newEnemy;
    }
}

int Creep::getNumberOfEnemy()
{
    return _enemies.size();
}

Creep* Creep::getEnemy(int index)
{
    if (index >= 0 && index < _enemies.size()) {
        return _enemies[index];
    }
    return nullptr;
}

bool Creep::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _info = info;
    _isAttack = false;
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-idle (1)");
    _model->setScale(0.8f);
    _model->setAnchorPoint(Vec2(0.7,0.5));
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Creep::callbackOnContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    Size size(_model->getContentSize().width / 1.5, _model->getContentSize().height / 1.4);
    auto enemyPhysicBody = PhysicsBody::createBox(size, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(true);
    this->setPhysicsBody(enemyPhysicBody);
    enemyPhysicBody->setTag(ENEMY_TAG);

    auto rangeAttackNode = Node::create();
    auto physicRangeAttackNode = PhysicsBody::createBox(_model->getContentSize() * 2);
    physicRangeAttackNode->setCategoryBitmask(0x030);
    physicRangeAttackNode->setCollisionBitmask(DefineBitmask::GROUND);
    physicRangeAttackNode->setRotationEnable(false);
    rangeAttackNode->setPhysicsBody(physicRangeAttackNode);
    rangeAttackNode->setPosition(Vec2::ZERO);

    this->addChild(rangeAttackNode);


    _enemyStateMachine = StateMachine::create(this);

    _enemyStateMachine->addState("idle", new EnemyIdleState());
    _enemyStateMachine->addState("attack", new EnemyAttackState());

    _enemyStateMachine->setCurrentState("idle");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Creep::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-idle");
    aniNames.push_back(_info->_entityName + "-attack");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Void/", name);
        AnimationUtils::createAnimation(name, 0.5f);
    }
    return true;
}

bool Creep::callbackOnContactBegin(PhysicsContact& contact)
{
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    target = (nodeA == this) ? (nodeB) : (nodeA);
    Vec2 enemyPosition = this->getPosition();
    Vec2 characterPosition = target->getPosition();
    float enemyHeight = this->getContentSize().height;
    if (target != nullptr) {
        if (enemyPosition.y + enemyHeight + 10.0f < characterPosition.y) {
            this->removeFromParentAndCleanup(true);
        }
    }

    return true;
}

void Creep::update(float dt) {
    EntityInfo info("character");
    Vec2 characterPosition = Character::getInstance(&info)->getCharacter(0)->getPosition();
    float creepPositionX = this->getPositionX();
    if (characterPosition.x > creepPositionX  + 20 && characterPosition.x < creepPositionX + 20 + 100) {
        _rightRange = true;
        _leftRange = false;
    }
    else if (characterPosition.x < creepPositionX - 20 && characterPosition.x > creepPositionX - 20 - 100) {
        _rightRange = false;
        _leftRange = true;
    }
    else {
        _rightRange = false;
        _leftRange = false;
    }
}




void Creep::shoot(float dt)
{
    bulletTimer += dt;

    if (_isAttack) {
        if (bulletTimer >= bulletInterval) {
            bulletTimer = 0.0f;
            _isAttack = false;
        }
        else {
            return;
        }
    }

    if (bulletTimer >= bulletInterval) {
        for (int i = 0; i < 3; ++i) {
            auto bullet = Skill::create(new EntityInfo("fireskill"));
            bullet->setPosition(this->getPosition());
            bullet->setOwner(this);
            this->getParent()->addChild(bullet, 4);
            auto bulletBody = bullet->getPhysicsBody();
            float xImpulse = (i == 0) ? 0 : ((i == 1) ? -250000 : 250000);
            if (bulletBody) {
                bulletBody->applyImpulse(Vec2(xImpulse, 500000));
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
    bulletInterval = 2.0f;
}

