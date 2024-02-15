#include "EnemyPatrolState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void EnemyPatrolState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Right");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::EnemyAnimationTag);
	_owner->getModel()->runAction(animate);
	//auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(100);
	/*if (mapNode != nullptr) {
		_map = dynamic_cast<GameMap*>(mapNode);
	}*/
	auto _newEnemyPositionX = _owner->getPositionX();
	auto _newEnemyPositionY = _owner->getPositionY();
	auto moveLeft = MoveTo::create(1, Vec2(_newEnemyPositionX - 50, _newEnemyPositionY));
	auto moveRight = MoveTo::create(1, Vec2(_newEnemyPositionX + 50, _newEnemyPositionY));
	//auto delay = DelayTime::create(1.0f);
	auto seq = Sequence::create(moveLeft, /*delay*/ moveRight, nullptr);
	auto repeatForever = RepeatForever::create(seq);

	_owner->runAction(repeatForever);
}

std::string EnemyPatrolState::updateState()
{

	if (_owner->getModel()->getPosition() == Vec2(-100, 0)
		&& _owner->getModel()->getPosition() == Vec2(100, 0))
	{
		return "idle";
	}
	
	return "patrol";
}

void EnemyPatrolState::exitState()
{
	State::exitState();
}
