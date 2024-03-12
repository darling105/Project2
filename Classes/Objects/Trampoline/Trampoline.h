#ifndef __TRAMPOLINE_H__
#define __TRAMPOLINE_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Trampoline : public Entity {
public:
	static Trampoline* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	bool _isPicked = false;
protected:
	bool loadAnimations() override;
	bool callbackOnContactBegin(PhysicsContact& contact);
	bool callbackOnContaceSeparate(PhysicsContact& contact);
	void update(float dt);
	StateMachine* _stateMachine;
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
};

#endif // !__TRAMPOLINE_H__