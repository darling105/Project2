#include "PupplePatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Pupple/Pupple.h"

void PupplePatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    float patrolSpeed = 250.0f;
    Vec2 moveLeft = Vec2(-patrolSpeed, 0);
    Vec2 moveRight = Vec2(patrolSpeed, 0);
    auto moveLeftAction = MoveBy::create(1.5f, moveLeft);
    auto moveRightAction = MoveBy::create(1.5f, moveRight);
    auto sequence = Sequence::create(
        CallFunc::create([this]() { movingRight = true; }),
        moveRightAction,
        CallFunc::create([this]() { movingRight = false; }),
        moveLeftAction,
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


std::string PupplePatrolState::updateState() {
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


void PupplePatrolState::exitState()
{
    State::exitState();
}