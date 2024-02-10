#ifndef __STAIR_H__
#define __STAIR_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class Stair : public Node {
public:
    static Stair* create(TMXObjectGroup* objectGroup);
protected:
    bool init(TMXObjectGroup* objectGroup);
    //bool onContactBegin(const PhysicsContact& contact);
};

#endif // !__STAIR_H__
