    #include "CameraFollow.h"

    CameraFollow* CameraFollow::create(Node* target, Rect fieldOfView, ButtonController* buttonController)
    {
        auto newObject = new CameraFollow();
        if (newObject != nullptr && newObject->init(target, fieldOfView, buttonController)) {
            newObject->autorelease();
            return newObject;
        }
        CC_SAFE_DELETE(newObject);
        return nullptr;
    }

    bool CameraFollow::init(Node* target, Rect fieldOfView, ButtonController* buttonController)
    {
        if (!target) {
            return false;
        }
        _target = target;
        _fieldOfView = fieldOfView;
        _buttonController = buttonController; // Lưu trữ con trỏ đến ButtonController
        _dirty = false;
        _previousPosition = target->getPosition();

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
        if (_previousPosition != targetPosition) {
            _previousPosition = targetPosition;
            _dirty = true;
        }
        else {
            _dirty = false;
        }

        // Di chuyển camera
        float left_x = _fieldOfView.getMinX();
        float down_y = _fieldOfView.getMinY();
        float right_x = _fieldOfView.getMaxX();
        float up_y = _fieldOfView.getMaxY();

        float positionx = clampf(targetPosition.x, left_x, right_x);
        float positiony = clampf(targetPosition.y, down_y, up_y);

        camera->setPosition(Vec2(positionx, positiony));

        // Cập nhật vị trí của ButtonController
        if (_buttonController) {
            _buttonController->setPosition(camera->getPosition());
        }
    }

    bool CameraFollow::isDirty() const
    {
        return _dirty;
    }
    