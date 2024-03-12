#include "GhostDesappearState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Ghost/Ghost.h"

void GhostDesappearState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-desappear");
    auto animate = RepeatForever::create(Animate::create(ani));

    _owner->getModel()->runAction(animate);
}


std::string GhostDesappearState::updateState() {
    auto _ghost = static_cast<Ghost*>(_owner);
    if (_ghost->_desappear) {
        return "footstep";
    }
    return "desappear";
}


void GhostDesappearState::exitState()
{
    State::exitState();
}
