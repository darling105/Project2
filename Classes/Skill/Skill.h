#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Skill : public Entity {
public:
	static const int SKILL_TAG = 15;
	static Skill* create(std::string skillName);
	virtual bool init(std::string skillName);
protected:
	Sprite* _model;
protected:
	bool callbackOnContactBegin(PhysicsContact& contact);
	CC_SYNTHESIZE(Entity*, _owner, Owner);
};

#endif // !__SKILL_H__
