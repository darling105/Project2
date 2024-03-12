#include "GhostAppearState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Ghost/Ghost.h"

void GhostAppearState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-appear");
    auto animate = RepeatForever::create(Animate::create(ani));

    _owner->getModel()->runAction(animate);

}


std::string GhostAppearState::updateState() {
    auto _ghost = static_cast<Ghost*>(_owner);
    if (_ghost->_appear ) {
        return "patrol";
    }
    return "appear";
}



void GhostAppearState::exitState()
{
    State::exitState();
}


