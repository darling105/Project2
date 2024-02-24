#include "Enemy.h"
#include "AnimationUtilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "Skill/Skill.h"

Enemy* Enemy::_instance;
std::vector<Enemy*> Enemy::_enemies;


Enemy* Enemy::getInstance(EntityInfo* info) {
    if (_instance == nullptr) {
        _instance = new Enemy();
        _instance->init(info);
        _instance->retain();
    }
    return _instance;
}

void Enemy::addEnemy(EntityInfo* info)
{
    Enemy* _newEnemy = new Enemy();
    if (_newEnemy->init(info)) {
        _enemies.push_back(_newEnemy);
    }
    else {
        delete _newEnemy;
    }
}

int Enemy::getNumberOfEnemy()
{
    return _enemies.size();
}

Enemy* Enemy::getEnemy(int index)
{
    if (index >= 0 && index < _enemies.size()) {
        return _enemies[index];
    }
    return nullptr;
}

bool Enemy::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _info = info;
    _isAttack = false;
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "-patrol (1)");
    _model->runAction(animate);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Enemy::callbackOnContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto enemyPhysicBody = PhysicsBody::createBox(_model->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::GROUND);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::CHARACTER);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(true);
    this->setPhysicsBody(enemyPhysicBody);
    enemyPhysicBody->setTag(ENEMY_TAG);
    _enemyStateMachine = StateMachine::create(this);

    _enemyStateMachine->addState("patrol", new EnemyPatrolState());
    _enemyStateMachine->addState("attack", new EnemyAttackState());

    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);

    return true;
}

bool Enemy::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "-patrol");
    aniNames.push_back(_info->_entityName + "-attack");
    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Enemy/Robot/", name);
        AnimationUtils::createAnimation(name, 0.5f);
    }
    return true;
}

bool Enemy::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info("character");
    auto character = Character::getInstance(&info);
    auto _character = character->getCharacter(0);
    nodeA = contact.getShapeA()->getBody()->getNode();
    nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA != this && nodeB != this) return false;
    target = (nodeA == this) ? (nodeB) : (nodeA);
    Vec2 enemyPosition = this->getPosition();
    Vec2 characterPosition = _character->getPosition();
    float enemyHeight = this->getContentSize().height;
    if (target != nullptr) {
        if (enemyPosition.y + enemyHeight + 10.0f <= characterPosition.y) {
            this->removeFromParentAndCleanup(true);
        }
    }

    return true;
}

void Enemy::update(float dt) {
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



void Enemy::onEnter()
{
    Entity::onEnter();
    this->scheduleUpdate();
    bulletInterval = 3.0f;
}


