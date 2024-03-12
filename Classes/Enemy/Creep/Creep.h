#ifndef __CREEP_H__
#define __CREEP_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Creep : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Creep* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void setupCreep(float patrolSpeed, Vec2 initialMoveDirection);
	float _patrolSpeed;
	Vec2 _initialMoveDirection;
	bool _isAttack = false;
	bool _rightRange = false;
	bool _leftRange = false;
protected:
	bool loadAnimations() override;
	StateMachine* _enemyStateMachine;
	bool callbackOnContactBegin(PhysicsContact& contact);
	bool callbackOnContactSeparate(PhysicsContact& contact);
	void onEnter() override;
	void update(float dt);
	void shoot(float dt);
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
	float timeSinceLastShot;
	float bulletTimer;
	float bulletInterval;
	float _distanceRight, _distanceLeft = 100.0f;
	bool _isContactCharacter = false;

};
#endif // !__CREEP_H__