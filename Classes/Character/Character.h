#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"
#include "State/CharacterClimbState.h"
#include "State/CharacterHurtState.h"
#include "HealthController/HealthController.h"
#include "Objects/Platform/Platform.h"

class Character : public Entity
{
public:
    static const int CHARACTER_TAG = 100;
    static Character* getInstance(EntityInfo* info);
    static void addCharacter(EntityInfo* info);
    static int getNumberOfCharacters();
    static Character* getCharacter(int index);
    void resetInstance();
    void jump();
    void moveLeft();
    void moveRight();
    void setLeftButtonDown(bool isPressed);
    void setUpButtonDown(bool isPressed);
    void setRightButtonDown(bool isPressed);
    void setDownButtonDown(bool isPressed);
    void setPauseButtonDown(bool isPressed);
    bool getLeftButtonDown() const { return _isLeftButtonDown; }
    bool getUpButtonDown() const { return _isUpButtonDown; }
    bool getRightButtonDown() const { return _isRightButtonDown; }
    bool getDownButtonDown() const { return _isDownButtonDown; }
    bool getPauseButtonDown() const { return _isPauseButtonDown; }
    void reset();
    static bool isMap1Completed() { return _isMap1Completed; }
    static void setMap1Completed(bool completed) { _isMap1Completed = completed; }
    bool _isJumping = false;
    bool _isOnStair = false;
    bool _isOnGround = false;
    bool _isOnFinish = false;
    bool _isOnSpike = false;
    bool _isContactedSkills = false;
    bool _isContactedEnemy = false;
    bool _isContactedCheckPoint = false;
    bool isFirstCheckpointContacted = false;
    bool isFirstCheckpointContacted1 = false;
    bool _isLeftButtonDown = false;
    bool _isUpButtonDown = false;
    bool _isRightButtonDown = false;
    void getMap(std::string mapLevel);
    std::string returnMap() { return mapLevel; };
private:
    static Character* _instance;
    static std::vector<Character*> _characters;
    bool init(EntityInfo* info) override;
    bool loadAnimations() override;
    PhysicsBody* physicBodyCharacter;
    StateMachine* _stateMachine;
    
    bool _isDownButtonDown = false;
    bool _isPickedCoin = false;
    bool _isPauseButtonDown = false;
    float _jumpCooldown;
    void onEnter() override;
    static bool _isMap1Completed;
protected:
    bool callbackOnContactBegin(PhysicsContact& contact);
    bool callbackOnContactSeparate(PhysicsContact& contact);
    void update(float dt);
    int _retryCount = 3;
    float _baseSpeed = 60;
    bool _gameOver;
    std::vector<PhysicsBody*> _groundList;
    std::vector<int> checkpointContacted;
    int indexCheckPoint = 0;
    Vec2 check;
    Vec2 check1;

    std::string mapLevel;
    bool _isOnPlatform = false;
 
};

#endif // !__CHARACTER_H__