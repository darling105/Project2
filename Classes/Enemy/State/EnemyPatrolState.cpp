#include "EnemyPatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Enemy.h"
#include "Enemy/Creep.h"

void EnemyPatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    float patrolSpeed = 60.0f;

    Vec2 velocityLeft = Vec2(-patrolSpeed, 0);
    Vec2 velocityRight = Vec2(patrolSpeed, 0);

    auto enemyBody = _owner->getPhysicsBody();
    if (enemyBody) {
        enemyBody->setVelocity(velocityLeft);
        auto delay = DelayTime::create(2.0f);
        auto changeDirection = CallFunc::create([enemyBody, velocityRight, this]() {
            enemyBody->setVelocity(velocityRight);
            movingRight = true;
            });

        auto changeDirectionBack = CallFunc::create([enemyBody, velocityLeft, this]() {
            enemyBody->setVelocity(velocityLeft);
            movingRight = false;
            });

        auto sequence = Sequence::create(delay, changeDirection, delay, changeDirectionBack, nullptr);
        auto repeat = RepeatForever::create(sequence);

        _owner->runAction(repeat);
    }

    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::EnemyAnimationTag);
    _owner->getModel()->runAction(animate);
}





std::string EnemyPatrolState::updateState() {
    EntityInfo info("robot");
    auto robotInstance = Enemy::getInstance(&info);
    auto robot = robotInstance->getEnemy(0);
    auto creepInstance = Creep::getInstance(&info);
    auto creep = robotInstance->getEnemy(0);

    if (movingRight) {
        _owner->getModel()->setFlippedX(false);
    }
    else {
        _owner->getModel()->setFlippedX(true);
    }

    if (robot->_isAttack && creep->_isAttack) {
        return "attack";
    }

    return "patrol";
}


void EnemyPatrolState::exitState()
{
    State::exitState();
}
