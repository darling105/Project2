#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "StateMachine/StateMachine.h"

USING_NS_CC;

class Bullet : public Entity {
public:
	static const int SKILL_TAG = 15;
	static Bullet* create(EntityInfo* info);
protected:
	bool callbackOnContactBegin(PhysicsContact& contact);
	virtual bool init(EntityInfo* info);
	bool loadAnimations() override;
	void update(float dt);
	void onEnter() override;
	CC_SYNTHESIZE(Entity*, _owner, Owner);
protected:
	Sprite* _model;
	bool _isCollidedGround;
	bool _isCollidedCharacter;
};

#endif // !__BULLET_H__