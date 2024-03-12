#ifndef __CHECK_POINT_H__
#define __CHECK_POINT_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class CheckPoint : public Node {
public:
    static CheckPoint* create(TMXObjectGroup* objectGroup);
protected:
    bool init(TMXObjectGroup* objectGroup);
protected:
    int checkpointCount = 0;
    bool _isContactCharacter;
    Node* nodeA;
    Node* nodeB;
    Node* target;
};

#endif // !__CHECK_POINT_H__
