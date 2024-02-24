#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Coin : public Entity {
public:
	static Coin* create(EntityInfo* info);
protected:
	virtual bool init(EntityInfo* info);
	bool loadAnimations() override;
};

#endif // !__COIN_H__
