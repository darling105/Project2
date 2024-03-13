#include "TinyDeathState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Tiny/Tiny.h"

void TinyDeathState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-death");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string TinyDeathState::updateState()
{
	return "death";
}

void TinyDeathState::exitState()
{
	State::exitState();
}