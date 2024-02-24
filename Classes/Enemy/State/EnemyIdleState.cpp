#include "EnemyIdleState.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/Creep.h"
void EnemyIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string EnemyIdleState::updateState()
{
	EntityInfo creepInfo("void");
	auto creepInstance = Creep::getInstance(&creepInfo);
	auto creep = creepInstance->getEnemy(0);
	if (creep->_rightRange || creep->_leftRange) {
		return "attack";
	}
	return "idle";
}

void EnemyIdleState::exitState()
{
	State::exitState();
}