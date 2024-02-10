#ifndef __PHYSIC_GROUND_H__
#define __PHYSIC_GROUND_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class PhysicGround : public Node {
public:
     static const int TAG_GROUND = 10;
     static const int TAG_GROUND_EDGE = 30;
     static PhysicGround* create(TMXObjectGroup* objectGroup);
protected:
     bool init(TMXObjectGroup* objectGroup);
     bool onContactBegin(const PhysicsContact& contact);
};

#endif // !__PHYSIC_GROUND_H__
