#include "VoidIdleState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Void/Void.h"
void VoidIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string VoidIdleState::updateState()
{
	return "idle";
}

void VoidIdleState::exitState()
{
	State::exitState();
}