#include "EnemyChaseState.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "Enemy/Enemy.h"

void EnemyChaseState::enterState(Entity* owner) {
    State::enterState(owner);
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Right");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    _owner->getModel()->runAction(animate);

}

std::string EnemyChaseState::updateState() {
    Vec2 characterPosition;

    // Get the character instance
    EntityInfo info(1, "character");
    Character* character = Character::getInstance(&info);
    characterPosition = character->getCharacter(0)->getPosition();
    EntityInfo info1(1, "Hero");
    Enemy* enemy = Enemy::getInstance(&info1);
    for (int i = 0; i < 4; i++) {
        auto enemyPosition = enemy->getEnemy(i)->getPosition();

        // Get the character position
        const float chaseRange = 50.0f;
        
        //log("%f %f", enemyPosition.x, enemyPosition.y);
        //log("Character Position - X: %f, Y: %f", characterPosition.x, characterPosition.y);

        if (characterPosition.x > enemyPosition.x - chaseRange &&
            characterPosition.x < enemyPosition.x + chaseRange &&
            characterPosition.y > enemyPosition.y - chaseRange &&
            characterPosition.y < enemyPosition.y + chaseRange) {
            enemy->getEnemy(i)->setPosition(Vec2(enemyPosition.x + chaseRange, enemyPosition.y + chaseRange));
            log("chasing");
            return "chase";
    }
    }

    // Return the default state if no chase condition is met
    return "chase";
}


void EnemyChaseState::exitState() {
    State::exitState();
}
