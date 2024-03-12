#include "BatPatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Bat/Bat.h"

void BatPatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto bat = static_cast<Bat*> (_owner);
    Vec2 moveDirection = bat->_initialMoveDirection;
    
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


std::string BatPatrolState::updateState() {
    if (movingRight) {
        _owner->getModel()->setFlippedX(true);
        _owner->getModel()->setAnchorPoint(Vec2(0.5, 0.5));
    }
    else {
        _owner->getModel()->setFlippedX(false);
        _owner->getModel()->setAnchorPoint(Vec2(0.5, 0.5));
    }
    auto bat = static_cast<Bat*> (_owner);
    if (bat->_isContactCharacter) {
        return "death";
    }
    return "patrol";
}


void BatPatrolState::exitState()
{
    State::exitState();
}

void BatPatrolState::movingLeftFirst()
{
    auto bat = static_cast<Bat*> (_owner);
    float patrolSpeed = bat->_patrolSpeed;
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

void BatPatrolState::movingRightFirst()
{
    auto bat = static_cast<Bat*> (_owner);
    float patrolSpeed = bat->_patrolSpeed;
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
