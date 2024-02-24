#include "CharacterRunState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void CharacterRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-run");
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
	EntityInfo info( "character");
	auto character = Character::getInstance(&info);
	auto _character = character->getCharacter(0);
	if (!_character->getLeftButtonDown() && !_character->getRightButtonDown()) {
		return "idle";
	}
	if (_character->_isJumping) {
		return "jump";
	}
	return "run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}