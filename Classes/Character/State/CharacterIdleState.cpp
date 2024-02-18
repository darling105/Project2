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
	EntityInfo info(1, "character");
	auto _characterInstace = Character::getInstance(&info);
	auto _character = _characterInstace->getCharacter(0);

	return "idle";
}

void CharacterIdleState::exitState()
{
	State::exitState();
}