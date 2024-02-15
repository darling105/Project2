#include "EnemyIdleState.h"
#include "StateMachine/StateMachine.h"
void EnemyIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Down");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string EnemyIdleState::updateState()
{
	/*auto keyboard = KeyboardInput::getInstance();

	if (_owner->getModel()->getPosition() > Vec2(-100, 0)
		&& _owner->getModel()->getPosition() < Vec2(100, 0))
	{
		return "patrol";
	}*/

	/*if (Vec2(300, _owner->getPositionY()) < _character->getPosition() && _character->getPosition() < Vec2(500, _owner->getPositionY())) {
		return "chase";
	}*/

	return "idle";
}

void EnemyIdleState::exitState()
{
	State::exitState();
}