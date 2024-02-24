#include "EnemyAttackState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Enemy.h"
#include "Enemy/Creep.h"
#include "StateMachine/State.h"

void EnemyAttackState::enterState(Entity* owner) {
    State::enterState(owner);
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-attack");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    _owner->getModel()->runAction(animate);

}

std::string EnemyAttackState::updateState() {
    EntityInfo creepInfo("void");
    auto creepInstance = Creep::getInstance(&creepInfo);
    auto creep = creepInstance->getEnemy(0);

    EntityInfo info("robot");
    auto robotInstance = Enemy::getInstance(&info);
    auto robot = robotInstance->getEnemy(0);

    if (!creep->_leftRange && !creep->_rightRange) {
        if (!robot->_isAttack) {
            return "patrol";
        }
        else {
            return "idle";
        }
    }

    if (creep->_rightRange) {
        creep->getModel()->setFlippedX(true);
        creep->getModel()->setAnchorPoint(Vec2(0.3, 0.5));
    }
    else if (creep->_leftRange) {
        creep->getModel()->setFlippedX(false);
        creep->getModel()->setAnchorPoint(Vec2(0.7, 0.5));
    }

    return "attack";
}







void EnemyAttackState::exitState() {
    State::exitState();
}
