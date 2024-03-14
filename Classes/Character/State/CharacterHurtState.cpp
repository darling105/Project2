#include "CharacterHurtState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void CharacterHurtState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-hurt");
	auto animate = RepeatForever::create(Animate::create(ani));
	_owner->getModel()->runAction(animate);
}

std::string CharacterHurtState::updateState()
{
	EntityInfo info("character");
	auto character = Character::getInstance(&info);
	auto _character = character->getCharacter(0);
	if (_character->getLeftButtonDown() || _character->getRightButtonDown()) {
		return "run";
	}
	if (_character->_isJumping) {
		return "jump";
	}
	if (_character->_isOnStair) {
		return "climb";
	}

	return "hurt";
}

void CharacterHurtState::exitState()
{
	State::exitState();
}