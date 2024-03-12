#include "CharacterJumpState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"

void CharacterJumpState::enterState(Entity* owner)
{
    State::enterState(owner);
    log("jump state");
    auto ani = AnimationCache::getInstance()
        ->getAnimation(owner->getEntityInfo()->_entityName + "-jump");
    auto animate = RepeatForever::create(Animate::create(ani));
    owner->getModel()->runAction(animate);
    auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(100);
    if (mapNode != nullptr) {
        _map = dynamic_cast<GameMap*>(mapNode);
    }
  
}

std::string CharacterJumpState::updateState()
{
    EntityInfo info("character");
    auto _characterInstace = Character::getInstance(&info);
    auto _character = _characterInstace->getCharacter(0);

    if (_character->getLeftButtonDown()) {
        _owner->getModel()->setFlippedX(true);
    }
    if (_character->getRightButtonDown()) {
        _owner->getModel()->setFlippedX(false);
    }

    if (!_character->_isJumping) {
        return "idle";
    }
    if (_character->_isOnStair) {
        return "climb";
    }
    return "jump";
}

void CharacterJumpState::exitState()
{
    State::exitState();
}



