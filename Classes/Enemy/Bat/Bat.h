#ifndef __BAT_H__
#define __BAT_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Bat : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Bat* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void setupBat(float patrolSpeed, Vec2 initialMoveDirection);
	float _patrolSpeed;
	Vec2 _initialMoveDirection;
	bool _isContactCharacter = false;
	bool _isContactGround = false;
protected:
	bool loadAnimations() override;
	StateMachine* _enemyStateMachine;
	bool callbackOnContactBegin(PhysicsContact& contact);
	bool callbackOnContactSeparate(PhysicsContact& contact);
	void update(float dt);
	void onEnter() override;
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
	float _maxSpeed;
	float timeDeath;

};
#endif // !__BAT_H__