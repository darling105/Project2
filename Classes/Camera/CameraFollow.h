#ifndef __CAMERA_FOLLOW_H__
#define __CAMERA_FOLLOW_H__

#include "cocos2d.h"
USING_NS_CC;

class CameraFollow :public Node
{
private:
	Node* _target;
	Rect _fieldOfView;
public:
	static CameraFollow* create(Node* target, Rect fieldOfView);

	virtual bool init(Node* target, Rect fieldOfView);

	void update(float dt);
};

#endif // !__CAMERA_FOLLOW_H__