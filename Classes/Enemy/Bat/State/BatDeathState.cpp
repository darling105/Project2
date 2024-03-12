#include "BatDeathState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Bat/Bat.h"

void BatDeathState::enterState(Entity* owner) {
    State::enterState(owner);
    _owner->stopAllActions();
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "-death");
    auto animate = RepeatForever::create(Animate::create(ani));
    _owner->getModel()->runAction(animate);
}


std::string BatDeathState::updateState() {
    return "death";
}


void BatDeathState::exitState()
{
    State::exitState();
}


