#include "PupplePatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Pupple/Pupple.h"

void PupplePatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto pupple = static_cast<Pupple*> (_owner);
    Vec2 moveDirection = pupple->_initialMoveDirection;

    if (moveDirection == Vec2(1.0f, 0.0f)) {
        movingRightFirst();
    }
    else if (moveDirection == Vec2(-1.0f, 0.0f)) {
        movingLeftFirst();
    }

    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(ani));
    _owner->getModel()->runAction(animate);
}


std::string PupplePatrolState::updateState() {
    if (movingRight) {
        _owner->getModel()->setFlippedX(true);
        _owner->getModel()->setAnchorPoint(Vec2(0.35, 0.35));
    }
    else {
        _owner->getModel()->setFlippedX(false);
        _owner->getModel()->setAnchorPoint(Vec2(0.6, 0.35));
    }
    return "patrol";
}


void PupplePatrolState::exitState()
{
    State::exitState();
}

void PupplePatrolState::movingLeftFirst()
{
    auto pupple = static_cast<Pupple*> (_owner);
    float patrolSpeed = pupple->_patrolSpeed;
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
}

void PupplePatrolState::movingRightFirst()
{
    auto pupple = static_cast<Pupple*> (_owner);
    float patrolSpeed = pupple->_patrolSpeed;
    Vec2 moveLeft = Vec2(-patrolSpeed, 0);
    Vec2 moveRight = Vec2(patrolSpeed, 0);
    auto moveLeftAction = MoveBy::create(2.0f, moveLeft);
    auto moveRightAction = MoveBy::create(2.0f, moveRight);
    auto sequence = Sequence::create(
        CallFunc::create([this]() { movingRight = true; }),
        moveRightAction,
        CallFunc::create([this]() { movingRight = false; }),
        moveLeftAction,
        nullptr
    );
    auto repeat = RepeatForever::create(sequence);
    _owner->runAction(repeat);
}
