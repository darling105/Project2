#include "CharacterIdleState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void CharacterIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string CharacterIdleState::updateState()
{
	EntityInfo info( "character");
	auto character = Character::getInstance(&info);
	auto _character = character->getCharacter(0);
	if (_character->getLeftButtonDown() || _character->getRightButtonDown()) {
		return "run";
	}
	if (_character->_isJumping) {
		return "jump";
	}

	return "idle";
}

void CharacterIdleState::exitState()
{
	State::exitState();
}