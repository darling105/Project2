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
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
    _model->runAction(animate);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Enemy::callbackOnContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto enemyPhysicBody = PhysicsBody::createBox(_model->getContentSize() / 3.3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    enemyPhysicBody->setCategoryBitmask(DefineBitmask::NON);
    enemyPhysicBody->setCollisionBitmask(DefineBitmask::NON);
    enemyPhysicBody->setContactTestBitmask(DefineBitmask::NON);
    enemyPhysicBody->setRotationEnable(false);
    enemyPhysicBody->setGravityEnable(false);
    this->setPhysicsBody(enemyPhysicBody);
    enemyPhysicBody->setTag(ENEMY_TAG);
    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("idle", new EnemyIdleState());
    _enemyStateMachine->addState("patrol", new EnemyPatrolState());
    _enemyStateMachine->addState("chase", new EnemyChaseState());
    _enemyStateMachine->setCurrentState("patrol");
    this->addChild(_enemyStateMachine);
    //schedule(CC_SCHEDULE_SELECTOR(Enemy::shoot), 10.0f);

    return true;
}

bool Enemy::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "_Idle_Down");
    aniNames.push_back(_info->_entityName + "_Idle_Right");
    aniNames.push_back(_info->_entityName + "_Jump_Down");

    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Character/", name);
        AnimationUtils::createAnimation(name, 2.0f);
    }
    return true;
}

bool Enemy::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info(1, "Hero");
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
    else {
        this->removeFromParentAndCleanup(true);
    }

    return true;
}

void Enemy::update(float dt) {
    // Cập nhật biến đếm thời gian
    bulletTimer += dt;
    // Kiểm tra nếu đã đến thời điểm bắn viên đạn tiếp theo
    if (bulletTimer >= bulletInterval) {
        for (int i = 0; i < 3; ++i) {
            auto bullet = Skill::create(new EntityInfo(1, "fireskill"));
            bullet->setPosition(this->getPosition());
            bullet->setOwner(this);
            this->getParent()->addChild(bullet, 4);
            auto bulletBody = bullet->getPhysicsBody();
            float xImpulse = (i == 0) ? 0 : ((i == 1) ? -250000 : 250000);
            if (bulletBody) {
                bulletBody->applyImpulse(Vec2(xImpulse, 500000));
            }
        }
        
        // Đặt lại biến đếm thời gian
        bulletTimer = 0.0f;
    }
}


void Enemy::onEnter()
{
    Entity::onEnter();
    this->scheduleUpdate();
    bulletInterval = 2.0f;
}


















