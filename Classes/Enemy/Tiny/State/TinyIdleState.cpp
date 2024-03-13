#include "TinyIdleState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Tiny/Tiny.h"

void TinyIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string TinyIdleState::updateState()
{
	auto _tiny = static_cast<Tiny*>(_owner);
	if (_tiny->_isMoving) {
		return "run";
	}
	return "idle";
}

void TinyIdleState::exitState()
{
	State::exitState();
}