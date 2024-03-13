#ifndef __TINY_H__
#define __TINY_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Tiny : public Entity
{
public:

	static Tiny* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void movingLeftFirst();
	void movingRightFirst();
	void setSpeed(float newVal);
	bool _isMoving = false;
	bool _jump = false;
	bool _explode = false;
	bool _dead = false;
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
	bool _isContactCharacter = false;
	float _patrolSpeed;

	bool movingRight = false;
	bool movingLeft = false;
	float _countTime;
	float _countExplode;
	float _countDeath;
	float _countRemove;

};
#endif // !__TINY_H__