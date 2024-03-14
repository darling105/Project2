#include "CharacterClimbState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void CharacterClimbState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-climb");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string CharacterClimbState::updateState()
{
	EntityInfo info("character");
	auto character = Character::getInstance(&info);
	auto _character = character->getCharacter(0);
	if (!_character->_isOnStair) {
		return "idle";
	}
	if (_character->_isContactedEnemy) {
		return "hurt";
	}
	return "climb";
}

void CharacterClimbState::exitState()
{
	State::exitState();
}
