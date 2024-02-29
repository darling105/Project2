#ifndef __SPIKE_H__
#define __SPIKE_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"

USING_NS_CC;

class Spike : public Node
{
public:
	static Spike* create(TMXObjectGroup* objectGroup);
protected:
	bool init(TMXObjectGroup* objectGroup);
};

#endif //!__SPIKE_H__