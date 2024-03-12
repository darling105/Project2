#include "WilliamIdleState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/William/William.h"

void WilliamIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string WilliamIdleState::updateState()
{
	auto william = static_cast<William*>(_owner);
	if (william->_leftRange) {
		william->getModel()->setFlippedX(false);
		william->getModel()->setAnchorPoint(Vec2(0.55, 0.4));
	}
	else if (william->_rightRange) {
		william->getModel()->setFlippedX(true);
		william->getModel()->setAnchorPoint(Vec2(0.45, 0.4));
	}
	return "idle";
}

void WilliamIdleState::exitState()
{
	State::exitState();
}