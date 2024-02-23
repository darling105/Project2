#ifndef __FINISH_H__
#define __FINISH_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class Finish : public Node {
public:
    static Finish* create(TMXObjectGroup* objectGroup);
protected:
    bool init(TMXObjectGroup* objectGroup);
    //bool onContactBegin(const PhysicsContact& contact);
};

#endif // !__STAIR_H__
