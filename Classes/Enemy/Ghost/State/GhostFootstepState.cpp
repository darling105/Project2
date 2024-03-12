#include "GhostFootstepState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Ghost/Ghost.h"

void GhostFootstepState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-footstep");
    auto animate = RepeatForever::create(Animate::create(ani));

    _owner->getModel()->runAction(animate);
}


std::string GhostFootstepState::updateState() {
    auto _ghost = static_cast<Ghost*>(_owner);
    if (_ghost->_footstep) {
        return "appear";
    }
    return "footstep";
}


void GhostFootstepState::exitState()
{
    State::exitState();
}
