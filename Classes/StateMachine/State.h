#ifndef __STATE_H__
#define __STATE_H__

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class State
{
public:
	virtual void enterState(Entity* owner);
	virtual std::string updateState();
	virtual void exitState();

protected:
	Entity* _owner;
};

#endif // !__STATE_H__
