#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Coin : public Entity {
public:
	static Coin* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	bool _isPicked = false;
protected:
	bool loadAnimations() override;
	bool callbackOnContactBegin(PhysicsContact& contact);
	void update(float dt);
	StateMachine* _stateMachine;
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
};

#endif // !__COIN_H__