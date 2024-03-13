#include "TinyRunState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Tiny/Tiny.h"

void TinyRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-run");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string TinyRunState::updateState()
{
	auto _tiny = static_cast<Tiny*>(_owner);
	if (_tiny->_jump) {
		return "jump";
	}
	return "run";
}

void TinyRunState::exitState()
{
	State::exitState();
}