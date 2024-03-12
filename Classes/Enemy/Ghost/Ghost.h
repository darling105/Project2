#ifndef __GHOST_H__
#define __GHOST_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Ghost : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Ghost* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void movingLeftFirst();
	void movingRightFirst();
	void setSpeed(float newVal);
	bool _appear = false;
	bool _desappear = false;
	bool _patrol = false;
	bool _footstep = false;
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

	float _countTime = 0.0f;
	float _countSpeed = 0.0f;
	bool movingRight = false;
	bool movingLeft = false;

};
#endif // !__GHOST_H__