#include "GhostDeathState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Ghost/Ghost.h"

void GhostDeathState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-death");
    auto animate = RepeatForever::create(Animate::create(ani));

    _owner->getModel()->runAction(animate);
}


std::string GhostDeathState::updateState() {
    /*if (movingRight) {
        _owner->getModel()->setFlippedX(true);
        _owner->getModel()->setAnchorPoint(Vec2(0.35, 0.35));
    }
    else {
        _owner->getModel()->setFlippedX(false);
        _owner->getModel()->setAnchorPoint(Vec2(0.6, 0.35));
    }*/
    return "death";
}


void GhostDeathState::exitState()
{
    State::exitState();
}
