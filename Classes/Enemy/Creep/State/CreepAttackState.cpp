#include "CreepAttackState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Creep/Creep.h"
#include "StateMachine/State.h"

void CreepAttackState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-attack");
    auto animate = RepeatForever::create(Animate::create(ani));
    _owner->getModel()->runAction(animate);
}

std::string CreepAttackState::updateState() {
    auto creep = static_cast<Creep*> (_owner);
    if (creep->_rightRange) {
        creep->getModel()->setFlippedX(true);
        creep->getModel()->setAnchorPoint(Vec2(0.3, 0.5));
    }
    else if (creep->_leftRange) {
        creep->getModel()->setFlippedX(false);
        creep->getModel()->setAnchorPoint(Vec2(0.7, 0.5));
    }
    if (!creep->_isAttack && !creep->_leftRange && !creep->_rightRange) {
        return "patrol";
    }

    return "attack";
}



void CreepAttackState::exitState() {
    State::exitState();
}