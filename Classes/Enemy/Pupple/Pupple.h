#ifndef __PUPPLE_H__
#define __PUPPLE_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Pupple : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Pupple* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
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
#endif // !__PUPPLE_H__