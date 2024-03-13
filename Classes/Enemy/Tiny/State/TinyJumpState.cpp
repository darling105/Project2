#include "TinyJumpState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Tiny/Tiny.h"

void TinyJumpState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-jump");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string TinyJumpState::updateState()
{
	auto _tiny = static_cast<Tiny*>(_owner);
	if (_tiny->_explode) {
		return "explode";
	}
	return "jump";
}

void TinyJumpState::exitState()
{
	State::exitState();
}