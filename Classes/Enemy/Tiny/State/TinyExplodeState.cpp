#include "TinyExplodeState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Tiny/Tiny.h"

void TinyExplodeState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-explode");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string TinyExplodeState::updateState()
{
	auto _tiny = static_cast<Tiny*>(_owner);
	if (_tiny->_dead) {
		return "death";
	}
	return "explode";
}

void TinyExplodeState::exitState()
{
	State::exitState();
}