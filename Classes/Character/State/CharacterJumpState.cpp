#include "CharacterJumpState.h"
#include "StateMachine.h"
#include "../Character.h"
#include "../../Entity/Entity.h"
#include "KeyBoardInput.h"

void CharacterJumpState::enterState(Entity* owner)
{
    State::enterState(owner);
    log("jump state");
    auto ani = AnimationCache::getInstance()
        ->getAnimation(owner->getEntityInfo()->_entityName + "_Jump_Down");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    owner->getModel()->runAction(animate);
    auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(100);
    if (mapNode != nullptr) {
        _map = dynamic_cast<GameMap*>(mapNode);
    }
    //isJumping = false;
  
}

std::string CharacterJumpState::updateState()
{
    if (KeyboardInput::getInstance()->getKey(EventKeyboard::KeyCode::KEY_SPACE)) {
        _owner->getPhysicsBody()->applyImpulse(Vec2(0, 1000));
    }
    return "jump";
}

void CharacterJumpState::exitState()
{
    State::exitState();
}

//void CharacterJumpState::jump()
//{
//    log("Jumping");
//    isJumping = true;
//}


