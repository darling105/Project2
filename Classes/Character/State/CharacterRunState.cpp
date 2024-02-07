#include "CharacterRunState.h"
#include "StateMachine.h"
#include "KeyBoardInput.h"

void CharacterRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Right");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);

	auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(100);
	if (mapNode != nullptr) {
		_map = dynamic_cast<GameMap*>(mapNode);
	}
}

std::string CharacterRunState::updateState()
{
	//auto keyboard = KeyboardInput::getInstance();
	//// update
	//Vec2 direction = keyboard->getDirection();
	//float dt = Director::getInstance()->getAnimationInterval();
	//Vec2 nextPosition = _owner->getPosition() + direction * 10 * dt;

	//if (_map->getMetaAtPos(nextPosition) != GameMap::MetaRed) {
	//	_owner->setPosition(nextPosition);
	//}

	//if (direction.x != 0)
	//	_owner->getModel()->setFlippedX(direction.x < 0);

	//// 
	//if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	//{
	//	return "jump";
	//}

	//if (keyboard->getDirection() == Vec2::ZERO)
	//{
	//	return "idle";
	//}
	return "run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}