    #include "CameraFollow.h"

    CameraFollow* CameraFollow::create(Node* target, Rect fieldOfView)
    {
        auto newObject = new CameraFollow();
        if (newObject != nullptr && newObject->init(target, fieldOfView)) {
            newObject->autorelease();
            return newObject;
        }
        CC_SAFE_DELETE(newObject);
        return nullptr;
    }

    bool CameraFollow::init(Node* target, Rect fieldOfView)
    {
        if (!target) {
            return false;
        }
        this->_target = target;
        this->_fieldOfView = fieldOfView;
        
        
        this->scheduleUpdate();
        return true;
    }

    void CameraFollow::update(float dt)
    {
        if (!_target)
            return;
       
        // Get the camera's position
        cocos2d::Camera* camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
        cocos2d::Vec2 targetPosition = _target->getPosition();
        cocos2d::Camera* buttonCam = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
        if (_previousPosition != targetPosition) {
            _previousPosition = targetPosition;
            _dirty = true;
        }
        else {
            _dirty = false;
        }
        if (buttonCam) {
            buttonCam->setPosition(targetPosition);
        }

        float left_x = _fieldOfView.getMinX();
        float down_y = _fieldOfView.getMinY();
        float right_x = _fieldOfView.getMaxX();
        float up_y = _fieldOfView.getMaxY();

        float positionx = clampf(targetPosition.x, left_x, right_x);
        float positiony = clampf(targetPosition.y, down_y, up_y);

        camera->setPosition(Vec2(positionx, positiony));

    }

    bool CameraFollow::isDirty() const
    {
        return _dirty;
    }
    