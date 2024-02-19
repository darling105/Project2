#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Skill : public Entity {
public:
	static const int SKILL_TAG = 15;
	static Skill* create(EntityInfo* info);
protected:
	bool callbackOnContactBegin(PhysicsContact& contact);
	virtual bool init(EntityInfo* info);
	bool loadAnimations() override;
	CC_SYNTHESIZE(Entity*, _owner, Owner);
};

#endif // !__SKILL_H__
