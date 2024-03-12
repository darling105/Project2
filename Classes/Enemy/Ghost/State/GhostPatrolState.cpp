#include "GhostPatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Ghost/Ghost.h"

void GhostPatrolState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-patrol");
    auto animate = RepeatForever::create(Animate::create(ani));
    _owner->getModel()->runAction(animate);
}


std::string GhostPatrolState::updateState() {
    auto _ghost = static_cast<Ghost*>(_owner);
    if (_ghost->_patrol) {
        return "desappear";
    }
    return "patrol";
}


void GhostPatrolState::exitState()
{
    State::exitState();
}
