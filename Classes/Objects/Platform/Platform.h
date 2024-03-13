#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Platform : public Entity
{
public:
	static Platform* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void movingLeftFirst();
	void movingRightFirst();
	void setSpeed(float newVal);
	float _patrolSpeed;
	Vec2 _initialMoveDirection;
	bool movingRight = false;
	bool movingLeft = false;
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
	float _countSpeed;


};
#endif // !__PLATFORM_H__