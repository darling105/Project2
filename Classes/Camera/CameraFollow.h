#ifndef __CAMERA_FOLLOW_H__
#define __CAMERA_FOLLOW_H__

#include "cocos2d.h"
#include "ButtonController/ButtonController.h"
USING_NS_CC;

class CameraFollow : public cocos2d::Node {
public:
    static CameraFollow* create(Node* target, Rect fieldOfView, ButtonController* buttonController);

    bool init(Node* target, Rect fieldOfView, ButtonController* buttonController);

    void update(float dt);

    bool isDirty() const;

private:
    Node* _target;
    Rect _fieldOfView;
    bool _dirty;
    ButtonController* _buttonController; // Thêm trường để lưu trữ con trỏ đến ButtonController
    cocos2d::Vec2 _previousPosition;
};

#endif // !__CAMERA_FOLLOW_H__