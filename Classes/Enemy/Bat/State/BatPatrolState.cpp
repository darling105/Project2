#include "BatPatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Bat/Bat.h"

void BatPatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    float patrolSpeed = 200.0f;
    Vec2 moveLeft = Vec2(-patrolSpeed, 0);
    Vec2 moveRight = Vec2(patrolSpeed, 0);
    auto moveLeftAction = MoveBy::create(2.0f, moveLeft);
    auto moveRightAction = MoveBy::create(2.0f, moveRight);
    auto sequence = Sequence::create(
        CallFunc::create([this]() { movingRight = false; }),
        moveLeftAction,
        CallFunc::create([this]() { movingRight = true; }),
        moveRightAction,
        nullptr
    );
    auto repeat = RepeatForever::create(sequence);
    _owner->runAction(repeat);

    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::EnemyAnimationTag);
    _owner->getModel()->runAction(animate);
}


std::string BatPatrolState::updateState() {
    if (movingRight) {
        _owner->getModel()->setFlippedX(true);
        _owner->getModel()->setAnchorPoint(Vec2(0.38, 0.5));
    }
    else {
        _owner->getModel()->setFlippedX(false);
        _owner->getModel()->setAnchorPoint(Vec2(0.6, 0.5));
    }
    return "patrol";
}


void BatPatrolState::exitState()
{
    State::exitState();
}