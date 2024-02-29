//#include "EnemyChaseState.h"
//#include "StateMachine/StateMachine.h"
//#include "Character/Character.h"
//#include "Enemy/Enemy.h"
//
//void EnemyChaseState::enterState(Entity* owner) {
//    State::enterState(owner);
//    auto ani = AnimationCache::getInstance()
//        ->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Right");
//    auto animate = RepeatForever::create(Animate::create(ani));
//    animate->setTag(StateMachine::AnimationTag);
//    _owner->getModel()->runAction(animate);
//
//}
//
//std::string EnemyChaseState::updateState() {
//    return "chase";
//}
//
//
//void EnemyChaseState::exitState() {
//    State::exitState();
//}
