#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"
#include "State/CharacterClimbState.h"

class Character : public Entity
{
public:
    static const int CHARACTER_TAG = 100;
    static Character* getInstance(EntityInfo* info);
    static void addCharacter(EntityInfo* info);
    static int getNumberOfCharacters();
    static Character* getCharacter(int index);
    void jump();
    void moveLeft();
    void moveRight();
    void setLeftButtonDown(bool isPressed);
    void setUpButtonDown(bool isPressed);
    void setRightButtonDown(bool isPressed);
    void setDownButtonDown(bool isPressed);
    bool getLeftButtonDown() const { return _isLeftButtonDown; }
    bool getUpButtonDown() const { return _isUpButtonDown; }
    bool getRightButtonDown() const { return _isRightButtonDown; }
    bool getDownButtonDown() const { return _isDownButtonDown; }
    bool _isJumping = false;
    bool _isOnStair = false;
    bool _isOnGround = false;
    bool _isOnFinish = false;
    bool _isOnSpike = false;
private:
    static Character* _instance;
    static std::vector<Character*> _characters;
    bool init(EntityInfo* info) override;
    bool loadAnimations() override;
    PhysicsBody* physicBodyCharacter;
    StateMachine* _stateMachine;
    bool _isLeftButtonDown = false;
    bool _isUpButtonDown = false;
    bool _isRightButtonDown = false;
    bool _isDownButtonDown = false;
    bool _isPickedCoin = false;
    bool _isContactEnemy = false;
    float _jumpCooldown;
    void onEnter() override;
    //void onExit() override;
protected:
    bool callbackOnContactBegin(PhysicsContact& contact);
    bool callbackOnContactSeparate(PhysicsContact& contact);
    void update(float dt) override;
};

#endif // !__CHARACTER_H__