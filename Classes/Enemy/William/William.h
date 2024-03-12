#ifndef __WILLIAM_H__
#define __WILLIAM_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class William : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static William* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
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
	void update(float dt);
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
#endif // !__WILLIAM_H__