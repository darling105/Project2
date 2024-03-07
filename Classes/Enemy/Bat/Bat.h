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
protected:
	bool loadAnimations() override;
	StateMachine* _enemyStateMachine;
	//bool callbackOnContactBegin(PhysicsContact& contact);
	//bool callbackOnContactSeparate(PhysicsContact& contact);
	void onEnter() override;
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
	bool _isContactCharacter = false;

};
#endif // !__BAT_H__