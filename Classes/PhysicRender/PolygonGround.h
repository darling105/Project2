#ifndef __POLYGON_GROUND_H__
#define __POLYGON_GROUND_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class PolygonGround : public Node {
public:
    static const int TAG_GROUND = 10;

    static PolygonGround* create(TMXObjectGroup* objectGroup);
protected:
    bool init(TMXObjectGroup* objectGroup);
    //bool onContactBegin(const PhysicsContact& contact);
};

#endif // !__POLYGON_GROUND_H__
