#ifndef __SAW_H__
#define __SAW_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Saw : public Entity
{
public:
	static Saw* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void movingLeftFirst();
	void movingRightFirst();
	void setSpeed(float newVal);
	float _patrolSpeed;
	Vec2 _initialMoveDirection;
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
	bool movingRight = false;
	bool movingLeft = false;
	float _countSpeed;

};
#endif // !__SAW_H__