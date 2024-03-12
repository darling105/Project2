#include "PuppleDeathState.h"
#include "StateMachine/StateMachine.h"

void PuppleDeathState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();

    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-death");
    auto animate = RepeatForever::create(Animate::create(ani));
    _owner->getModel()->runAction(animate);
}


std::string PuppleDeathState::updateState() {
    return "death";
}


void PuppleDeathState::exitState()
{
    State::exitState();
}


